import tensorflow as tf
from tensorflow.keras import models, layers, datasets
from ml_genn import Model
from ml_genn.utils import parse_arguments, raster_plot
import numpy as np
from six import iteritems
from time import perf_counter


if __name__ == '__main__':
    args = parse_arguments('Simple CNN classifier model')
    print('arguments: ' + str(vars(args)))

    for gpu in tf.config.experimental.list_physical_devices('GPU'):
        tf.config.experimental.set_memory_growth(gpu, True)

    # Retrieve and normalise MNIST dataset
    (x_train, y_train), (x_test, y_test) = datasets.cifar10.load_data()
    x_train = x_train[:args.n_train_samples] / 255.0
    y_train = y_train[:args.n_train_samples]
    x_test = x_test[:args.n_test_samples] / 255.0
    y_test = y_test[:args.n_test_samples]
    x_norm = x_train[np.random.choice(x_train.shape[0], args.n_norm_samples, replace=False)]

    # Create, train and evaluate TensorFlow model
    tf_model = models.Sequential([
        layers.Conv2D(32, (3,3), padding='same', activation='relu',  use_bias=False, input_shape=x_train.shape[1:]),
        layers.Conv2D(32, (3,3), padding='same', activation='relu',  use_bias=False),
        layers.AveragePooling2D(2),
        layers.Dropout(0.2),

        layers.Flatten(),
        layers.Dense(y_train.max() + 1, activation='softmax', use_bias=False),

    ], name='simple_cnn')

    """
    ## TEMP:
    tf_model = models.Sequential([
        layers.Conv2D(32, (3,3), padding='same', activation='relu',  use_bias=False, input_shape=x_train.shape[1:]),
        layers.Activation('elu'),
        layers.BatchNormalization(),
        layers.Conv2D(32, (3,3), padding='same', activation='relu',  use_bias=False),
        layers.Activation('elu'),
        layers.BatchNormalization(),
        layers.MaxPooling2D(pool_size=(2,2)),
        layers.Dropout(0.2),

        layers.Conv2D(64, (3,3), padding='same', activation='relu',  use_bias=False),
        layers.Activation('elu'),
        layers.BatchNormalization(),
        layers.Conv2D(64, (3,3), padding='same', activation='relu',  use_bias=False),
        layers.Activation('elu'),
        layers.BatchNormalization(),
        layers.MaxPooling2D(pool_size=(2,2)),
        layers.Dropout(0.3),

        layers.Conv2D(128, (3,3), padding='same', activation='relu',  use_bias=False),
        layers.Activation('elu'),
        layers.BatchNormalization(),
        layers.Conv2D(128, (3,3), padding='same', activation='relu',  use_bias=False),
        layers.Activation('elu'),
        layers.BatchNormalization(),
        layers.MaxPooling2D(pool_size=(2,2)),
        layers.Dropout(0.4),

        layers.Flatten(),
        layers.Dense(y_train.max() + 1, activation='softmax', use_bias=False),

    ], name='simple_cnn')

    """


    """
    # ORIGINAL
    # Create, train and evaluate TensorFlow model
    tf_model = models.Sequential([
        layers.Conv2D(32, (3, 3), padding='same', activation='relu',  use_bias=False),
        layers.AveragePooling2D(2),
        layers.Conv2D(64, (3, 3), padding='same', activation='relu',  use_bias=False),
        layers.AveragePooling2D(2),
        layers.Flatten(),
        layers.Dense(128, activation='relu', use_bias=False),
        layers.Dense(64, activation='relu', use_bias=False),
        layers.Dense(y_train.max() + 1, activation='softmax', use_bias=False),
    ], name='simple_cnn')
    """
    """
    # simple CNN for CIFAR10. 1 epoch @1.5k = 54s @ .46acc
    )
    Conv2D(32, (3, 3), activation='relu', kernel_initializer='he_uniform', padding='same'))
    MaxPooling2D((2, 2)))
    Conv2D(64, (3, 3), activation='relu', kernel_initializer='he_uniform', padding='same'))
    Conv2D(64, (3, 3), activation='relu', kernel_initializer='he_uniform', padding='same'))
    MaxPooling2D((2, 2)))
    Conv2D(128, (3, 3), activation='relu', kernel_initializer='he_uniform', padding='same'))
    Conv2D(128, (3, 3), activation='relu', kernel_initializer='he_uniform', padding='same'))
    MaxPooling2D((2, 2)))
    """

    """
    # Vgg16 CNN for CIFAR10. UNTESTED
    model = Sequential()
    Conv2D(32, (3,3), padding='same', activation='relu',  use_bias=False), input_shape=x_train.shape[1:]))
    Activation('elu'))
    BatchNormalization())
    Conv2D(32, (3,3), padding='same', activation='relu',  use_bias=False)))
    Activation('elu'))
    BatchNormalization())
    MaxPooling2D(pool_size=(2,2)))
    Dropout(0.2))

    Conv2D(64, (3,3), padding='same', activation='relu',  use_bias=False)))
    Activation('elu'))
    BatchNormalization())
    Conv2D(64, (3,3), padding='same', activation='relu',  use_bias=False)))
    Activation('elu'))
    BatchNormalization())
    MaxPooling2D(pool_size=(2,2)))
    Dropout(0.3))

    Conv2D(128, (3,3), padding='same', activation='relu',  use_bias=False)))
    Activation('elu'))
    BatchNormalization())
    Conv2D(128, (3,3), padding='same', activation='relu',  use_bias=False)))
    Activation('elu'))
    BatchNormalization())
    MaxPooling2D(pool_size=(2,2)))
    Dropout(0.4))

    Flatten())
    Dense(num_classes, activation='softmax'))

    model.summary()
    """

    if args.reuse_tf_model:
        tf_model = models.load_model('KYP_P12_FS_CIFAR10')
    else:
        tf_model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
        tf_model.fit(x_train, y_train, epochs=1)
        models.save_model(tf_model, 'KYP_P12_FS_CIFAR10', save_format='h5')

    tf_eval_start_time = perf_counter()
    scores = tf_model.evaluate(x_test, y_test)
    print("TF evaluation:%f" % (perf_counter() - tf_eval_start_time))
    print("\nTest result: %.3f loss: %.3f" % (scores[1]*100,scores[0]))

    # Create a suitable converter to convert TF model to ML GeNN
    converter = args.build_converter(x_norm, signed_input=False, K=8, norm_time=500)

    ifcontinue = input("Convert to SNN w/ GeNN (y/n): ")
    if ifcontinue != "y":
        exit()

    # Convert and compile ML GeNN model
    mlg_model = Model.convert_tf_model(
        tf_model, converter=converter, connectivity_type=args.connectivity_type,
        dt=args.dt, batch_size=args.batch_size, rng_seed=args.rng_seed,
        kernel_profiling=args.kernel_profiling)

    time = 8 if args.converter == 'few-spike' else 500
    mlg_eval_start_time = perf_counter()
    acc, spk_i, spk_t = mlg_model.evaluate([x_test], [y_test], time, save_samples=args.save_samples)
    print("MLG evaluation:%f" % (perf_counter() - mlg_eval_start_time))

    if args.kernel_profiling:
        print("Kernel profiling:")
        for n, t in iteritems(mlg_model.get_kernel_times()):
            print("\t%s: %fs" % (n, t))

    # Report ML GeNN model results
    print('Accuracy of CIFAR10 GeNN model: {}%'.format(acc[0]))
    if args.plot:
        neurons = [l.neurons.nrn for l in mlg_model.layers]
        raster_plot(spk_i, spk_t, neurons, time=time)
