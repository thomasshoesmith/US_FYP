import numpy as np
import matplotlib.pyplot as plt
from os import path

from pygenn.genn_model import (create_custom_neuron_class,
                               create_custom_current_source_class,
                               create_custom_weight_update_class,
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
# # TODO: Custom weight update model
# ----------------------------------------------------------------------------

"""
        ### From GeNN Team Documentation ###
def pygenn.genn_model.create_custom_weight_update_class 	(
            class_name,
		  	param_names = None,
		  	var_name_types = None,
		  	pre_var_name_types = None,
		  	post_var_name_types = None,
		  	derived_params = None,
		  	sim_code = None,                                   # after a spike
		  	event_code = None,                                 # after an event        [uses of events vs spikes?]
		  	learn_post_code = None,
		  	synapse_dynamics_code = None,                      # sim code custom for each synapse
		  	event_threshold_condition_code = None,             # to trigger the event code
		  	pre_spike_code = None,
		  	post_spike_code = None,
		  	pre_dynamics_code = None,                          # alternative to synapse pre_dynamics_code, this will execute to the connections leaving a node
		  	post_dynamics_code = None,                         # executes to the connections to a neuron.
		  	sim_support_code = None,
		  	learn_post_support_code = None,
		  	synapse_dynamics_suppport_code = None,
		  	extra_global_params = None,
		  	is_pre_spike_time_required = None,
		  	is_post_spike_time_required = None,
		  	is_pre_spike_event_time_required = None,
		  	is_prev_pre_spike_time_required = None,
		  	is_prev_post_spike_time_required = None,
		  	is_prev_pre_spike_event_time_required = None,
		  	custom_body = None
	) """

fs_post_synpase_connection = create_custom_weight_update_class(
    'fs_relu_synapse',
    param_names=['K', 'alpha', 'elim'], #k = timesteps, alpha = highest value, elim = length of exponent
    derived_params=[("scale", create_dpf_class(lambda pars, dt: pars[1] * 2**(-pars[0]))())],
    var_name_types=[('input', 'scalar', VarAccess_READ_ONLY_DUPLICATE), ('Vmem', 'scalar'), ('scaleVal', 'scalar')],
    sim_code="""
    // # TODO: move sim from custom neuron class into custom synpase class
    """,
    event_threshold_condition_code='''
    $(Vmem) >= hT
    ''',
    event_code='''
    $(Vmem) -= hT;
    '''
    )

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

    // check pipetimestep < K
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
    const scalar hT = $(scale) * (1 << (kInt - (1 + (pipeTimestep % kInt))));
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



# Create first neuron
pop1 = model.add_neuron_population("neuron1", 1, fs_input_model, FS_INPUT_PARAM, ini_input)

# Create second neuron
pop2 = model.add_neuron_population("neuron2", 1, fs_model, FS_PARAM, ini)

# Create third neuron
pop3 = model.add_neuron_population("neuron3", 1, fs_model, FS_PARAM, ini)

# ----------------------------------------------------------------------------
# Parameters for synapse
# ----------------------------------------------------------------------------

s_ini = {"g": 1.0} #weight

ps_p = {"tau": 0.0, # Decay time constant [ms]
        "E": 0.0} # Reversal potential [mV]

# synapse connection between neurons 1 & 2
model.add_synapse_population(
    "synapse1", "DENSE_INDIVIDUALG", 0,
    pop1, pop2,
    "StaticPulse", {}, s_ini, {}, {},
    "DeltaCurr", {}, {})

# synapse connection between neurons 2 & 3
model.add_synapse_population(
    "synapse2", "DENSE_INDIVIDUALG", 0,
    pop2, pop3,
    "StaticPulse", {}, s_ini, {}, {},
    "DeltaCurr", {}, {})

model.build()
model.load()

# ----------------------------------------------------------------------------
# Displaying Vmem | Fx | Spiking output
# ----------------------------------------------------------------------------

timesteps = 24


p1_npspike = []
p2_npspike = []
p3_npspike = []

#Vmem across neurons
p1_Vmem = np.empty((timesteps, 1))
p1_view_Vmem = pop1.vars["Vmem"].view

p2_Vmem = np.empty((timesteps, 1))
p2_view_Vmem = pop2.vars["Vmem"].view

p3_Vmem = np.empty((timesteps, 1))
p3_view_Vmem = pop3.vars["Vmem"].view

#fx across >1 neurons
p2_Fx = np.empty((timesteps, 1))
p2_view_Fx = pop2.vars["Fx"].view

p3_Fx = np.empty((timesteps, 1))
p3_view_Fx = pop3.vars["Fx"].view

count = 0
model.t = 0.0
model.timestep = 0
while count < timesteps:
    print("timestep:", model.t, "\n")
    model.step_time()

    # neuron 1
    pop1.pull_var_from_device("Vmem")
    p1_Vmem[count - 1,:]=p1_view_Vmem[0]
    pop1.pull_current_spikes_from_device()
    p1_npspike.append(pop1.current_spikes.shape[0])

    # neuron 2
    pop2.pull_var_from_device("Vmem")
    p2_Vmem[count - 1,:]=p2_view_Vmem[0]
    pop2.pull_var_from_device("Fx")
    p2_Fx[count - 1,:]=p2_view_Fx[0]
    pop2.pull_current_spikes_from_device()
    p2_npspike.append(pop2.current_spikes.shape[0])

    # neuron 3
    pop3.pull_var_from_device("Vmem")
    p3_Vmem[count - 1,:]=p3_view_Vmem[0]
    pop3.pull_var_from_device("Fx")
    p3_Fx[count - 1,:]=p3_view_Fx[0]
    pop3.pull_current_spikes_from_device()
    p3_npspike.append(pop3.current_spikes.shape[0])

    if model.t == 8:
        model.t = 0.0
        model.timestep = 0

    count += 1

# creating height of the spikes to match the input value
for i in range(len(p1_npspike)):
    p1_npspike[i] = ini_input.get("input") * p1_npspike[i]
    p2_npspike[i] = ini_input.get("input") * p2_npspike[i]
    p3_npspike[i] = ini_input.get("input") * p3_npspike[i]


fig, axis = plt.subplots(3, figsize=(5, 10))

plt.subplots_adjust(left=0.1,
                    bottom=0.2,
                    right=0.9,
                    top=0.9,
                    wspace=1.0,
                    hspace=1.0)

fig.suptitle(("Input:" , ini_input.get("input")), fontsize=14)

# Vmem values
axis[0].set_title("FS Neuron ( Vmem )")
axis[0].plot(p1_Vmem, label="Neuron 1 Vmem", color='b')
axis[0].plot(p2_Vmem, label="Neuron 2 Vmem", color='r')
axis[0].plot(p3_Vmem, label="Neuron 3 Vmem", color='g')
axis[0].legend()
#axis[0].set_ylim(-1, ini_input.get("input") + 2)


# Fx values (neurons 23)
axis[1].set_title("FS Neuron ( Fx )")
axis[1].plot(p2_Fx, label="Neuron 2 Fx", color='r')
axis[1].plot(p3_Fx, label="Neuron 3 Fx", color='g')
axis[1].legend()
axis[1].set_ylim(-1, ini_input.get("input") + 2)

# output spike trains for neuron 1, 2  3
axis[2].set_title("Spike train")
axis[2].bar(np.arange(timesteps), p1_npspike, 0.1, color='b', label = "Neuron 1 Spikes")
axis[2].bar(np.arange(timesteps), p2_npspike, 0.1, color='r', label = "Neuron 2 Spikes")
axis[2].bar(np.arange(timesteps), p3_npspike, 0.1, color='g', label = "Nauron 3 Spikes")
axis[2].legend()



plt.xlabel("pipeline (K)")
plt.ylabel("Membrane Voltage (Vmem)")

plt.show()

#print(p1_npspike)

# ----------------------------------------------------------------------------
# Testing Playbox | code cemetery
# ----------------------------------------------------------------------------

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


"""
// Notes on adding a synapse pop
model.add_synapse_population("Pop1self", "SPARSE_GLOBALG", 10 =(delay, "NO_DELAY", or just put 0),
    pop1, pop1, <= connections
    "StaticPulse" (predefined *update model*, needs creating), {}(parameters), s_ini(synaptic variables), {}(pre), {}(post),
    "ExpCond" ("DeltaCurr"!, should work), ps_p (parameters), {} (initial values for variables),
    init_connectivity(ring_model, {})) (initialiser for the connections, default is fully connected)
"""

# Dan Goodman Imperial

# Sheffield - Stephie

# UCL L


## bigger picture
