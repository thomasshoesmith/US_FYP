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
# Parameters for all neurons
# ----------------------------------------------------------------------------

TIMESTEP = 1.0
PRESENT_TIMESTEPS = 100
INPUT_CURRENT_SCALE = 1.0 / 100.0

# ----------------------------------------------------------------------------
# Parameters for FS Input Neuron
# ----------------------------------------------------------------------------

FS_INPUT_PARAM =  {"K":       8.0,      # K timestep length
                   "alpha":   20.0,     # alpha "max" Value
                   "elim":    4.0}      # elim number of bits to represent the exponent

# ----------------------------------------------------------------------------
# Custom GeNN models
# Input FS ReLU model
# ----------------------------------------------------------------------------
fs_input_model = create_custom_neuron_class(
    'fs_relu_input',
    param_names=['K', 'alpha', 'elim'], #k = timesteps, alpha = highest value, elim = length of exponent
    derived_params=[("scale", create_dpf_class(lambda pars, dt: pars[1] * 2**(-pars[0]))())],
    var_name_types=[('input', 'scalar', VarAccess_READ_ONLY_DUPLICATE), ('Vmem', 'scalar'), ('scaleVal', 'scalar')],
    sim_code='''
    // Convert K to integer
    const int kInt = (int)$(K);

    // Get timestep within presentation | mod to keep within range
    const int pipeTimestep = (int)($(t) / DT);

    // If this is the first timestep, apply input
    if(pipeTimestep == 0) {
        $(Vmem) = $(input);
    }

    // check pipetimestep < 8
    const scalar hT = $(scale) * (1 << (kInt - ((pipeTimestep % kInt)+1)));

    $(scaleVal) = $(scale) * (1 << (kInt - ((pipeTimestep % kInt)+1)));
    ''',
    threshold_condition_code='''
    $(Vmem) >= hT
    ''',
    reset_code='''
    $(Vmem) -= hT;
    ''',
    is_auto_refractory_required=False)

# ----------------------------------------------------------------------------
# Parameters for post-input neurons
# ----------------------------------------------------------------------------

FS_PARAM =  {"K":             8.0,      # K timestep length
             "alpha":         20.0,     # alpha "max" Value
             "upstreamAlpha": 20.0}     # ? assume same

# ----------------------------------------------------------------------------
# Custom GeNN models
# Post Input FS ReLU model
# ----------------------------------------------------------------------------

fs_model = create_custom_neuron_class(
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
ini_input = {"input": 17.0,  # input Value
             "Vmem": 0.0,   # voltage membrane value
             "scaleVal": 0.0}

# Inital values for second neuron
ini = {"Fx": 0.0,  # input Value
       "Vmem": 0.0}   # voltage membrane value



# Create first neuron layer
pop1 = model.add_neuron_population("neuron1", 1, fs_input_model, FS_INPUT_PARAM, ini_input)

pop2 = model.add_neuron_population("neuron2", 1, fs_model, FS_PARAM, ini)

# ----------------------------------------------------------------------------
# Parameters for synapse
# ----------------------------------------------------------------------------

s_ini = {"g": 1.0} #weight

ps_p = {"tau": 0.0, # Decay time constant [ms]
        "E": 0.0} # Reversal potential [mV]

model.add_synapse_population(
    "synapse1", "DENSE_INDIVIDUALG", NO_DELAY,
    pop1, pop2,
    "StaticPulse", {}, s_ini, {}, {},
    "DeltaCurr", {}, {})

"""
// Notes on adding a synapse pop
model.add_synapse_population("Pop1self", "SPARSE_GLOBALG", 10 =(delay, "NO_DELAY", or just put 0),
    pop1, pop1, <= connections
    "StaticPulse" (predefined *update model*, needs creating), {}(parameters), s_ini(synaptic variables), {}(pre), {}(post),
    "ExpCond" ("DeltaCurr"!, should work), ps_p (parameters), {} (initial values for variables),
    init_connectivity(ring_model, {})) (initialiser for the connections, default is fully connected)
"""

# ----------------------------------------------------------------------------
# Displaying Vmem
# ----------------------------------------------------------------------------

model.build()
model.load()

p1 = np.empty((8, 1))
p1_view = pop1.vars["Vmem"].view
p1_spike = pop1.current_spikes

p2 = np.empty((8, 1))
p2_view = pop2.vars["Fx"].view

print(p2_view)

"""#duplicate
s = np.empty((8, 1))
s_view = pop1.vars["scaleVal"].view"""

print(p1_view.shape)


while model.t < 8.0:
    model.step_time()

    pop1.pull_var_from_device("Vmem")
    pop1.pull_current_spikes_from_device()
    p1[model.timestep - 1,:]=p1_view[0]
    #print(p1[model.timestep - 1, :])

    pop2.pull_var_from_device("Fx")
    p2[model.timestep - 1,:]=p2_view[0]

"""    pop1.pull_var_from_device("scaleVal")

    s[model.timestep - 1,:]=s_view[1]"""


fig, axis = plt.subplots()
axis.plot(p1, label="population 1")
axis.plot(p2, label="population 2")
plt.xlabel("pipeline (K)")
plt.ylabel("Membrane Voltage (Vmem)")
plt.title("FS Neuron")
plt.legend(loc="upper left")
plt.show()



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


"""
## TODO: Graph not displaying expected results.

Shouldn't Fx be delayed by x_timesteps
"""

# dan goodman Imperial
