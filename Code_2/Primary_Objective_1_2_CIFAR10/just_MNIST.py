import tensorflow as tf
from tensorflow.keras import models, layers, datasets
from ml_genn import Model
from ml_genn.utils import parse_arguments, raster_plot
import numpy as np



if __name__ == '__main__':
    args = parse_arguments('Simple CNN classifier model')
    print('arguments: ' + str(vars(args)))

    for gpu in tf.config.experimental.list_physical_devices('GPU'):
        tf.config.experimental.set_memory_growth(gpu, True)

    # Retrieve and normalise MNIST dataset
    (mnist_x_train, mnist_y_train),(mnist_x_test, mnist_y_test) = \
    datasets.mnist.load_data()

    # Testing Shape of mnist
    print("\n### MNIST ###")
    print("individual MNIST shape:\t\t", mnist_x_train[0].shape)
    print("Pre Overall MNIST shape:\t", mnist_x_train.shape)
    mnist_x_train = mnist_x_train.reshape((-1, 28, 28, 1)) / 255.0
    print("Post Overall MNIST shape:\t", mnist_x_train.shape)



    # Retrieve and normalise CIFAR10 dataset
    (cifar10_x_train, cifar10_y_train),(cifar10_x_test, cifar10_y_test) = \
    datasets.cifar10.load_data()

    # Testing Shape of mnist
    print("\n### CIFAR10 ###")
    print("individual CIFAR10 shape:\t", cifar10_x_train[0].shape)
    print("Pre Overall CIFAR10 shape:\t", cifar10_x_train.shape)
    #cifar10_x_train = cifar10_x_train.reshape((1000, 3, 32, 32))
    #print("Post Overall CIFAR10 shape:\t", cifar10_x_train.shape)


    """
    print("\n### MNIST ###")
    print(mnist_x_train[0])

    print("\n### CIFAR10 ###")
    print(cifar10_x_train[0])
    """



#memory usage pros and cons
