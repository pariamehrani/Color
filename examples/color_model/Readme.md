The color model is implemented in TarzaNN. Before running the model, TarzaNN must be properly installed. The color model can be found in the "examples/color_model". In the color model directory, the shell script, "run_color_model.sh", provides a usage example for running the code. 

* NOTE that the input image is assumed to be converted to LMS cone activations. Refer to the paper for the code to be employed for this conversion. 

* The cone input weights to LGN and also V2-V4 weights employed in our experiments are provided in text files in the main color model directory.

* The data employed in our exmperiments can be found in the directory called "data". This directory includes an LMS-converted hue wheel image, a directory called "noticeable_hue_stimuli" containing the 60 sampled hues explained in the paper, and a directory called "single_hue_stimuli" which containes the stimuli employed for the hue reconstruction experiment.

* By default, the V4 feature maps will be saved in the directory called "results".
