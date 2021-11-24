import tensorflow as tf
from ml_genn import Model

#TENSORFLOW ANN
mnist = tf.keras.datasets.mnist

(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0


tf_model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape=(28, 28)),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(10)
])


tf_model.compile(optimizer='adam',
                 loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                 metrics=['accuracy'])


tf_model.fit(x_train, y_train, epochs=5)


print("success of tensorflow SNN")


#START OF ANN TO SNN CONVERSION
ml_genn_model = Model.convert_tf_model(tf_model)
#ml_genn_model.evaluate([x_train], [y_train], 300.0)
