import numpy as np
import matplotlib.pyplot as plt
from os import path

from pygenn.genn_model import (create_custom_neuron_class,
                               create_custom_current_source_class,
                               GeNNModel,
                               create_dpf_class)
from pygenn.genn_wrapper import NO_DELAY
from pygenn.genn_wrapper.Models import VarAccess_READ_ONLY_DUPLICATE


# ----------------------------------------------------------------------------
# Parameters
# ----------------------------------------------------------------------------

FS_PARAM =  {"K":       8.0,      # K timestep length
             "alpha":   20.0,     # alpha "max" Value
             "elim":    4.0}      # elim number of bits to represent the exponent

TIMESTEP = 1.0
PRESENT_TIMESTEPS = 100
INPUT_CURRENT_SCALE = 1.0 / 100.0

# ----------------------------------------------------------------------------
# Custom GeNN models
# Input FS ReLU model
# ----------------------------------------------------------------------------
fs_relu_input_model = create_custom_neuron_class(
    'fs_relu_input',
    param_names=['K', 'alpha', 'elim'], #k = timesteps, alpha = highest value, elim = length of exponent
    derived_params=[("scale", create_dpf_class(lambda pars, dt: pars[1] * 2**(-pars[0]))())],
    var_name_types=[('input', 'scalar', VarAccess_READ_ONLY_DUPLICATE), ('Vmem', 'scalar'), ('scaleVal', 'scalar')],
    sim_code='''
    // Convert K to integer
    const int kInt = (int)$(K);

    // Get timestep within presentation
    const int pipeTimestep = (int)($(t) / DT);

    // If this is the first timestep, apply input
    if(pipeTimestep == 0) {
        $(Vmem) = $(input);
    }

    const scalar hT = $(scale) * (1 << (kInt - (pipeTimestep+1)));

    $(scaleVal) = $(scale) * (1 << (kInt - (pipeTimestep+1)));
    ''',
    threshold_condition_code='''
    $(Vmem) >= hT
    ''',
    reset_code='''
    $(Vmem) -= hT;
    ''',
    is_auto_refractory_required=False)

# ----------------------------------------------------------------------------
# Parameters
# ----------------------------------------------------------------------------

FS_RELU_PARAM =  {"K":             8.0,      # K timestep length
                  "alpha":         20.0,     # alpha "max" Value
                  "upstreamAlpha": 20.0}     # ?

# ----------------------------------------------------------------------------
# Custom GeNN models
# Hidden layer FS ReLU model
# ----------------------------------------------------------------------------

fs_relu_model = create_custom_neuron_class(
    'fs_relu',
    param_names=['K', 'alpha', 'upstreamAlpha'],
    derived_params=[("scale", create_dpf_class(lambda pars, dt: pars[1] * 2**(-pars[0]))()),
                    ("upstreamScale", create_dpf_class(lambda pars, dt: pars[2] * 2**(-pars[0]))())],
    var_name_types=[('Fx', 'scalar'), ('Vmem', 'scalar')],
    sim_code='''
    // Convert K to integer
    const int kInt = (int)$(K);

    // Get timestep within presentation
    const int pipeTimestep = (int)($(t) / DT);

    // Calculate magic constants. For RelU hT=h=T
    // **NOTE** d uses last timestep as that was when spike was SENT
    const scalar hT = $(scale) * (1 << (kInt - (1 + pipeTimestep)));
    const scalar d = $(upstreamScale) * (1 << ((kInt - pipeTimestep) % kInt));

    // Accumulate input
    // **NOTE** needs to be before applying input as spikes from LAST timestep must be processed
    $(Fx) += ($(Isyn) * d);

    // If this is the first timestep, apply input
    if(pipeTimestep == 0) {
        $(Vmem) = $(Fx);
        $(Fx) = 0.0;
    }
    ''',
    threshold_condition_code='''
    $(Vmem) >= hT
    ''',
    reset_code='''
    $(Vmem) -= hT;
    ''',
    is_auto_refractory_required=False)


# ----------------------------------------------------------------------------
# Build model
# ----------------------------------------------------------------------------
# Create GeNN model
model = GeNNModel("float", "FS_singleNetwork")
model.dT = TIMESTEP

# Initial values to initialise all neurons to
ini = {"input": 17.0,  # input Value
       "Vmem": 0.0,   # voltage membrane value
       "scaleVal": 0.0}

# Inital values for second neuron
ini_relu = {"Fx": 0.0,  # input Value
            "Vmem": 0.0}   # voltage membrane value



# Create first neuron layer
pop1 = model.add_neuron_population("neuron1", 2, fs_relu_input_model, FS_PARAM, ini)

pop2 = model.add_neuron_population("neuron2", 2, fs_relu_model, FS_RELU_PARAM, ini_relu)

# ----------------------------------------------------------------------------
# Parameters for synapse
# ----------------------------------------------------------------------------

s_ini = {"g": 0.0}

ps_p = {"tau": 0.0, # Decay time constant [ms]
        "E": 0.0} # Reversal potential [mV]

model.add_synapse_population(
    "synapse1", "DENSE_INDIVIDUALG", NO_DELAY,
    pop1, pop1,
    "StaticPulse", {}, s_ini, {}, {},
    "DeltaCurr", {}, {})

"""
model.add_synapse_population("Pop1self", "SPARSE_GLOBALG", 10,
    pop1, pop1,
    "StaticPulse", {}, s_ini, {}, {},
    "ExpCond", ps_p, {},
    init_connectivity(ring_model, {}))
"""

"""
model.add_synapse_population("Pop1self", "SPARSE_GLOBALG", 10 =(delay, "NO_DELAY", or just put 0),
    pop1, pop1, <= connections
    "StaticPulse" (predefined update model, needs creating), {}(parameters), s_ini(synaptic variables), {}(pre), {}(post),
    "ExpCond" ("DeltaCurr"!, should work), ps_p (parameters), {} (initial values for variables),
    init_connectivity(ring_model, {})) (initialiser for the connections, default is fully connected)

"""

model.build()
model.load()

"""v = np.empty((8, 1))
v_view = pop1.vars["Vmem"].view

#duplicate
s = np.empty((8, 1))
s_view = pop1.vars["scaleVal"].view

while model.t < 8.0:
    model.step_time()
    pop1.pull_var_from_device("Vmem")

    v[model.timestep - 1,:]=v_view[:]

    pop1.pull_var_from_device("scaleVal")

    s[model.timestep - 1,:]=s_view[:]

fig, axis = plt.subplots()
axis.plot(v)
plt.xlabel("pipeline (K)")
plt.ylabel("Membrane Voltage (Vmem)")
plt.title("FS Neuron")"""


# ----------------------------------------------------------------------------
# Testing Playbox
# ----------------------------------------------------------------------------

#print(s)
#print(v)
"""
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

print("fs conversion\n\n",ini.get("input"), "->", ''.join(getSpikeTrain()))"""


#plt.show()
