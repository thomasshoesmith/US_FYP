import tensorflow as tf
from tensorflow.keras import models, layers, datasets
import tensorflow_datasets as tfds
import matplotlib.pyplot as plt

import numpy as np

#(x_train, y_train), (x_test, y_test) = datasets.mnist.load_data()


(x_train, y_train), (x_test, y_test) = tfds.as_numpy(tfds.load(
    'cifar10',
    split=['train', 'test'],
    batch_size=-1,
    as_supervised=True,
))

print(len(x_train))
print(len(x_test))
plt.imshow(x_train[0])
plt.show()
print(x_train[0])
print(x_train[0].shape)

"""
model = tf.keras.models.Sequential([
  tf.keras.layers.Flatten(input_shape=(28, 28)),
  tf.keras.layers.Dense(128, activation='relu'),
  tf.keras.layers.Dense(10)
])
model.compile(
    optimizer=tf.keras.optimizers.Adam(0.001),
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
    metrics=[tf.keras.metrics.SparseCategoricalAccuracy()],
)

#model.fit(x_train, y_train, epochs=2, validation_data=ds_test)

"""



