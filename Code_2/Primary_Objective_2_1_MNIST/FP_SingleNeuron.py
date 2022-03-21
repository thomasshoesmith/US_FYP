"""

model.dT = 0.1




pop1 = model.add_neuron_population("Pop1", 10, "TraubMiles", p, ini)"""


from pygenn.genn_model import GeNNModel
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

pop1 = model.add_neuron_population("Pop1", 2, "fp_relu_input", p, ini)
model.build()
model.load()
