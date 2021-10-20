from pygenn.genn_model import GeNNModel
model = GeNNModel("float", "tenHH")
model.dT = 0.1
p = {"gNa": 7.15,   # Na conductance in [muS]
     "ENa": 50.0,   # Na equi potential [mV]
     "gK": 1.43,    # K conductance in [muS]
     "EK": -95.0,   # K equi potential [mV]
     "gl": 0.02672, # leak conductance [muS]
     "El": -63.563, # El: leak equi potential in mV,
     "C": 0.143}    # membr. capacity density in nF
ini = {"V": -60.0,      # membrane potential
       "m": 0.0529324,  # prob. for Na channel activation
       "h": 0.3176767,  # prob. for not Na channel blocking
       "n": 0.5961207}  # prob. for K channel activation
pop1 = model.add_neuron_population("Pop1", 10, "TraubMiles", p, ini)
model.build()
