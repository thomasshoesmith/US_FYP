# FS Input Neurons

#imports
import numpy as np
from pygenn.genn_model import create_dpf_class, create_custom_neuron_class
from pygenn.genn_wrapper.Models import VarAccess_READ_ONLY_DUPLICATE

from ml_genn.layers.base_neurons import BaseNeurons #base level neuron, replacing "inpit_neurons"

#weight update module class

#fs neuron class
fs_relu_input_model = create_custom_neuron_class(
    'fs_relu_input',
    param_names=['K', 'alpha'],
    derived_params=[("scale", create_dpf_class(lambda pars, dt: pars[1] * 2**(-pars[0]))())],
    var_name_types=[('input', 'scalar', VarAccess_READ_ONLY_DUPLICATE), ('Vmem', 'scalar')],
    sim_code='''
    // Convert K to integer
    const int kInt = (int)$(K);

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

#FSReluInputNeuros class
class FSReluInputNeurons(BaseNeurons):
    def __init__(self, K=10, alpha=25, signed_input=False):
        super(FSReluInputNeurons, self).__init__()
        self.K = K
        self.alpha = alpha
        self.signed_input = signed_input

    def compile(self, mlg_model, layer):
        model = (fs_relu_signed_input_model if self.signed_input
                 else fs_relu_input_model)
        params = {'K' : self.K, 'alpha': self.alpha}
        vars = {'input': 0.0, 'Vmem': 0.0}

        super(FSReluInputNeurons, self).compile(mlg_model, layer, model,
                                                params, vars, {})

FSReluInputNeurons(8, 25, False)

#FS class (function)
class FewSpikes():
    def __init__(self, K=10, alpha=25, signed_input=False, norm_data=None):
        self.K = K
        self.alpha = alpha
        self.signed_input = signed_input
        self.norm_data = norm_data

    def create_input_neurons(self, pre_convert_output):
        alpha = (self.alpha if pre_convert_output.input_alpha is None
                 else pre_convert_output.input_alpha)
        return FSReluInputNeurons(self.K, alpha, self.signed_input)
