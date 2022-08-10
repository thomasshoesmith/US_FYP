
"""from pygenn.genn_model import GeNNModel
from ml_genn.layers import FPReluNeurons
from ml_genn.layers import FPReluInputNeurons

import matplotlib.pyplot as plt
import numpy as np
from pygenn.genn_model import (GeNNModel, init_connectivity, create_cmlf_class,
                               create_custom_sparse_connect_init_snippet_class)
from pygenn.genn_wrapper import NO_DELAY


model = GeNNModel("float", "fp_input")

model.dT = 0.1

p = {"K": 8,        # K timestep length
     "alpha": 20,   # alpha "max" Value
     "elim": 4}     # elim number of bits to represent the exponent

ini = {"input": 7,  # input Value
       "Vmem": 0}   # voltage membrane value

pop1 = model.add_neuron_population("Pop1", 2, "FPReluInputNeurons", p, ini)
model.build()
model.load()

derived_params=[("mantissa_scale", create_dpf_class(lambda pars, dt: pars[1] * 2 ** -fminf((2** pars[2] - 1), fmaxf(0.0, ceil(log2(1 / ( input / pars[1]))))) * 2 * 2**(-pars[0]))),
                ("exponent_scale", create_dpf_class(lambda pars, dt: 16.0 * 2 ** ( - pars[2])))], #TODO pars[0] = K, pars[1] = Alpha

"""


import numpy as np
import matplotlib.pyplot as plt
from os import path
import math

from pygenn.genn_model import (create_custom_neuron_class,
                               create_custom_current_source_class,
                               GeNNModel,
                               create_dpf_class)
from pygenn.genn_wrapper import NO_DELAY
from pygenn.genn_wrapper.Models import VarAccess_READ_ONLY_DUPLICATE


# ----------------------------------------------------------------------------
# Parameters
# ----------------------------------------------------------------------------

FP_PARAM =  {"K":       8.0,      # K timestep length
             "alpha":   20.0,     # alpha "max" Value
             "elim":    2.0}      # elim number of bits to represent the exponent

TIMESTEP = 1.0
PRESENT_TIMESTEPS = 100
INPUT_CURRENT_SCALE = 1.0 / 100.0

# ----------------------------------------------------------------------------
# Custom GeNN models
# ----------------------------------------------------------------------------

## TODO: clean up var_name_types, many used for testing
fp_relu_input_model = create_custom_neuron_class(
    'fp_relu_input',
    param_names=['K', 'alpha', 'elim'], #k = timesteps, alpha = highest value, elim = length of exponent
    var_name_types=[('input',   'scalar', VarAccess_READ_ONLY_DUPLICATE),
                    ('Vmem',    'scalar'),
                    ('scaleVal','scalar'),
                    ('measure', 'scalar'),
                    ('exponent','scalar'),
                    ('hT',      'scalar')],
    sim_code='''
    // Convert K to integer
    const int kInt = (int)$(K);

    // Convert Alpha to integer
    const int AlphaInt = (int)$(alpha);

    // Convert elim to integer
    const int elimInt = (int)$(elim);

    // Get timestep within presentation
    const int pipeTimestep = (int)($(t) / DT);

    //printf("%d", pipeTimestep);

    // If this is the first timestep, apply input
    if(pipeTimestep == 0) {

        $(scaleVal) = AlphaInt * pow(2, - fmin(pow(2, elimInt - 1), fmaxf(0, ceil(log2(1 / ($(input) / AlphaInt))))));
        //printf("%.6f", $(scaleVal));

        // needs to be cleaned up
        // scaleVal can be derived from exponent
        //# TODO: update variable names to logial ones
        $(exponent) = fmin(pow(2, elimInt - 1), fmaxf(0, ceil(log2(1 / ($(input) / AlphaInt)))));
        printf(" Exponent:%.6f ", $(exponent));
        //printf(" ScaleVal:%.6f ", $(scaleVal));

        $(Vmem) = $(exponent);
        $(measure) = $(exponent);

    }

    if (pipeTimestep == elimInt) {
        $(Vmem) = $(input);
        //printf("Value: %d", pipeTimestep);
    }

    $(hT) = 0;
    $(measure) = 0;

    if (pipeTimestep >= elimInt) {

        $(hT) = $(scaleVal) / (1 << (pipeTimestep - 4));

        $(measure) = $(scaleVal) / (1 << (pipeTimestep - 4));

        //printf(" Value:%d ", pipeTimestep);
    } else {

        $(hT) = pow(2, elimInt-1) / (1 << pipeTimestep);

        $(measure) = pow(2, elimInt-1) / (1 << pipeTimestep);

    }
    //printf(" pTs:%dhT:%.6f ", pipeTimestep, $(hT));

    ''',
    threshold_condition_code='''
    $(Vmem) >= $(hT)
    ''',
    reset_code='''
    $(Vmem) -= $(hT);
    ''',
    is_auto_refractory_required=False)


# ----------------------------------------------------------------------------
# Build model
# ----------------------------------------------------------------------------
# Create GeNN model
model = GeNNModel("float", "FP_singleNetwork")
model.dT = TIMESTEP

# Initial values to initialise all neurons to
ini = {"input": 7.23,  # input Value
       "Vmem": 0.0,   # voltage membrane value
       "scaleVal": 0.0,
       "measure": 0.0,  #testing
       "exponent": 0.0,
       "hT": 0.0}

# Create first neuron layer
neuron_layers = model.add_neuron_population("neuron1", 1,
                                             fp_relu_input_model, FP_PARAM, ini)


model.build()
model.load()

v = np.empty((8, 1))
v_view = neuron_layers.vars["Vmem"].view

print(v_view)

#duplicate
s = np.empty((8, 1))
s_view = neuron_layers.vars["measure"].view

p1_npspike = []

while model.t < 8.0:
    model.step_time()
    neuron_layers.pull_var_from_device("Vmem")

    v[model.timestep - 1,:]=v_view[:]

    neuron_layers.pull_var_from_device("measure")

    s[model.timestep - 1,:]=s_view[:]

    p1_npspike.append(neuron_layers.current_spikes.shape[0])

fig, axis = plt.subplots()
axis.plot(v, label="Vmem")
axis.plot(s, label="hT")
plt.xlabel("pipeline (K)")
plt.ylabel("Voltage Value")
plt.title("FP Input Neuron")
plt.axvline(x=FP_PARAM.get("elim"), color='r', linestyle='dotted')
plt.axhline(y=0, color='r', linestyle='dotted')
plt.legend()
plt.show()


plt.title("Spike Train from Input FP Neuron")
plt.bar(np.arange(8), p1_npspike, 0.1, color='b')
plt.xlabel("Timestep")
plt.ylabel("Spike (Bool)")
plt.legend()
plt.show()

# ----------------------------------------------------------------------------
# Testing Playbox
# ----------------------------------------------------------------------------

print("\n")
print(s)
print(v)

def getSpikeTrain():
    z = []
    if ini.get("input") > s[0]:
        z.append("1")
    else:
        z.append("0")

    for i in range(len(v)-1):
        if v[i] >= s[i+1]:
            z.append("1")
        else:
            z.append("0")
    return z

print("fp conversion\n\n",ini.get("input"), "->", ''.join(getSpikeTrain()))
