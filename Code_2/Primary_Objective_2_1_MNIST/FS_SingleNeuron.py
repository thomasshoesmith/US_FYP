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
# Build model
# ----------------------------------------------------------------------------
# Create GeNN model
model = GeNNModel("float", "FS_singleNetwork")
model.dT = TIMESTEP

# Initial values to initialise all neurons to
ini = {"input": 17.0,  # input Value
       "Vmem": 0.0,   # voltage membrane value
       "scaleVal": 0.0}

# Create first neuron layer
model.add_neuron_population("neuron1", 1,
                                             fs_relu_input_model, FS_PARAM, ini)

model.add_neuron_population("neuron2", 1,
                                             fs_relu_input_model, FS_PARAM, ini)

model.add_synapse_population(
    "synapse1", "DENSE_INDIVIDUALG", NO_DELAY,
    neuron1, neuron2,
    "StaticPulse", {}, {"g": w.flatten()}, {}, {},
    "DeltaCurr", {}, {})

model.build()
model.load()

v = np.empty((8, 1))
v_view = neuron_layers.vars["Vmem"].view

#duplicate
s = np.empty((8, 1))
s_view = neuron_layers.vars["scaleVal"].view

while model.t < 8.0:
    model.step_time()
    neuron_layers.pull_var_from_device("Vmem")

    v[model.timestep - 1,:]=v_view[:]

    neuron_layers.pull_var_from_device("scaleVal")

    s[model.timestep - 1,:]=s_view[:]

fig, axis = plt.subplots()
axis.plot(v)
plt.xlabel("pipeline (K)")
plt.ylabel("Membrane Voltage (Vmem)")
plt.title("FS Neuron")


# ----------------------------------------------------------------------------
# Testing Playbox
# ----------------------------------------------------------------------------

#print(s)
#print(v)

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

print("fs conversion\n\n",ini.get("input"), "->", ''.join(getSpikeTrain()))


#plt.show()
