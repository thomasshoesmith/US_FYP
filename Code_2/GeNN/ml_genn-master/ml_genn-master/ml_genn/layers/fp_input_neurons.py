from pygenn.genn_model import create_dpf_class, create_custom_neuron_class
from pygenn.genn_wrapper.Models import VarAccess_READ_ONLY_DUPLICATE
from ml_genn.layers.input_neurons import InputNeurons

fp_relu_input_model = create_custom_neuron_class(
    'fp_relu_input',
    param_names=['K', 'alpha', 'elim'], #k = timesteps, alpha = highest value, elim = length of exponent
    derived_params=[("mantissa_scale", create_dpf_class(lambda pars, dt: pars[1] * 2 ** -fminf((2** pars[2] - 1), fmaxf(0.0, ceil(log2(1 / ( input / pars[1]))))) * 2 * 2**(-pars[0]))),
                    ("exponent_scale", create_dpf_class(lambda pars, dt: 16.0 * 2 ** ( - pars[2])))], #TODO pars[0] = K, pars[1] = Alpha

    var_name_types=[('input', 'scalar', VarAccess_READ_ONLY_DUPLICATE), ('Vmem', 'scalar')],

    sim_code='''
    // Convert K to integer
    const int kInt = (int)$(K);

    // *Convert elim to integer
    const int elimInt = (int)$(elim);

    // Get timestep within presentation
    const int pipeTimestep = (int)($(t) / DT);

    // If this is the first timestep, apply input
    if(pipeTimestep == 0) {
        $(Vmem) = $(input);
    }

    const scalar hT = $(scale) * (1 << (kInt - (1 + pipeTimestep)));

    ''',
    threshold_condition_code='''
    $(Vmem) >= hT
    ''',
    reset_code='''
    $(Vmem) -= hT;
    ''',
    is_auto_refractory_required=False)

class FPReluInputNeurons(InputNeurons):
    def __init__(self, K=10, alpha=25, elim = 4):
        super(FPReluInputNeurons, self).__init__()
        self.K = K
        self.alpha = alpha
        self.elim = elim

    def compile(self, mlg_model, layer):
        model = fp_relu_input_model
        params = {'K' : self.K, 'alpha': self.alpha, 'elim' : self.elim}
        vars = {'input': 0.0, 'Vmem': 0.0}

        super(FPReluInputNeurons, self).compile(mlg_model, layer, model,
                                                params, vars, {})


# sparse_individualg
# dense_individualg (caps) (use this one)


"""
model.add_synapse_population("Pop1self", "SPARSE_GLOBALG", 10 =(delay, "NO_DELAY", or just put 0),
    pop1, pop1, <= connections
    "StaticPulse" (predifined update model, needs creating), {}(parameters), s_ini(synaptic variables), {}(pre), {}(post),
    "ExpCond" ("DeltaCurr", should work), ps_p (parameters), {} (initial values for variables),
    init_connectivity(ring_model, {})) (initialiser for the connections, default is fully connected)

"""
