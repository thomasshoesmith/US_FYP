from pygenn import genn_wrapper, genn_model
from pygenn.genn_model import create_dpf_class, create_custom_neuron_class

# GENN model for FS-Neuron

# Standard FS ReLU model where upstream neurons are FS ReLU or FS unsigned input
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



print("\n\n\nGENN model for FS-Neuron compiled\n\n\n")


######################## practice #########################

model = genn_model.GeNNModel("float", "izhikevich")
model.dT = 0.1

izk_init = {"V": -65.0,
            "U": -20.0,
            "a": [0.02, 0.1, 0.02, 0.02],
            "b": [0.2, 0.2, 0.2, 0.2],
            "c": [-65.0, -65.0, -50.0, -55.0],
            "d": [8.0, 2.0, 2.0, 4.0]}

pop = model.add_neuron_population("Pop", 4, "IzhikevichVariable", {}, izk_init)
model.add_current_source("CS", "DC", "Pop", {"amp": 10.0}, {})

model.build()
model.load()

v = pop.vars["V"].view
while model.t < 2.0:
    model.step_time()
    model.pull_state_from_device("Pop")
    print("%f, %f, %f, %f, %f" % (model.t, v[0], v[1], v[2], v[3]))


#=========== Few-Spikes Neuron ===========#
# x = input 
# K = timesteps K = 1, ... t 
# α = value representation range (cap)

def fs(x, K = 10, alpha = 25):
    t = 0
    fx = 0
    v =  np.zeros(K)
    z = np.zeros(K) 

    T = alpha * 2**(-K) * np.array([float(2 ** (K - i)) for i in range(1, K + 1)]).astype(np.float32)
    h = alpha * 2**(-K) * np.array([float(2 ** (K - i)) for i in range(1, K + 1)]).astype(np.float32)

    v[0] = x

    while t < K:         
        # spike if voltage > threshold, reset if spike.
        if v[t] >= T[t]:
            z[t] = 1
            v[t] = v[t] - h[t]  

        # copy over value once reduced.
        if t + 1 < K:
            v[t + 1] =  v[t] # no need to reduce further as this has already been shortened.

        # sum voltage if spike
        fx += z[t] * h[t] #* 0.5
        t += 1

    return z, fx # outputs tuple of spike train and sum (sum for configuration)


"""


### Jamie's FP Conversion code ###
import bitarray.util as bu
import math
def encode(x, alpha, exp_bits, mantissa_bits):
    # Calculate maximum mantissa value
    max_exp = (2 ** exp_bits) - 1
    # Calculate what integer equivalent of mantissa of one will be
    mantissa_one = 2 ** mantissa_bits
    # Get fraction of alpha we need to encode
    relative_x = x / alpha
    assert relative_x < 1.0
    # Calculate integer exponent (will be < 1) and clamp
    exponent = math.ceil(math.log2(relative_x))
    exponent = max(-max_exp, min(0, exponent))
    # Calculate value this exponent will represent
    exponent_value = 2 ** exponent
    # Calculate floating point mantissa value
    mantissa = relative_x / exponent_value
    assert mantissa < 1.0
    # Convert mantissa to fixed point bitarray and (negated) exponent to bitarray
    return (bu.int2ba(round(mantissa * mantissa_one), length=mantissa_bits),
            bu.int2ba(-exponent, length=exp_bits))
            
def decode(value, alpha):
    # Calculate what integer equivalent of mantissa of one will be
    mantissa_one = 2.0 ** len(value[0])
    # Extract components
    exp = bu.ba2int(value[1])
    mantissa = bu.ba2int(value[0])
    # Re-assemble floating point value
    return alpha * (2.0 ** -exp) * (mantissa / mantissa_one)


alpha = 20.0
code = encode(1, alpha, 4, 8)
#print(code)
#print(decode(code, alpha))



"""




print("file executed successfully")


