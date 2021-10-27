from ml_genn.layers.fs_input_neurons import fs_relu_input_model, fs_relu_signed_input_model
from ml_genn.layers.fs_neurons import fs_relu_model, fs_relu_upstream_signed_input_model
from pygenn.genn_model import GeNNModel,init_connectivity

K = 16
alpha = 5.0

model = GeNNModel("float", "trail", backend="SingleThreadedCPU")

model.dT = 0.1

model.build()
model.load()



print("success")
