import tensorflow as tf
import tensorflow_datasets as tfds

print("import sucessful")

(ds_train, ds_test), ds_info = tfds.load(
    'mnist',
    split=['train', 'test'],
    shuffle_files=True,
    as_supervised=True,
    with_info=False,
)



print("build successful")
