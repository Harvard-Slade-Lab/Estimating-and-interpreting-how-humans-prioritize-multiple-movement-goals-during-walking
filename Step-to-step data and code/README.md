Brief summary of the main scripts and functions used to analyze the motion capture data in this research project:

+ RunMultipleTrials: this is the main script, which processes the raw data from the .mat files corresponding to each trial of every participant. It produces two outputs: an Excel file containing parameters for visual inspection (such as step width, step width variability, step length, step length variability, step error, walking speed, and the median of selected values), and a .mat file that stores all the calculated variables for further analysis. For steps where the software is uncertain whether to classify a movement as a step or as a trip, a figure is displayed showing the displacement of the heel marker within the relevant frame window. The user can then decide whether to classify the movement as a step, a decision that may also be supported by visual inspection of the raw motion capture data. These user decisions are saved so that if the script is re-run for the same dataset, the process can be skipped by setting the parameter "usedecisions" to 1. This script relies on the following functions to calculate gait variables for each condition:

- LocateMarkers: locates all floor markers (FL) that define the walking track, as well as the position of the foot placement targets.

- LocateSteps: detects the exact frame and timing of each step made with the right or left foot. If the classification is uncertain, the user is prompted to decide whether the movement should be considered a step by typing "Y" (yes) or "N" (no) in the command window.

- StepError: calculates both absolute and signed step error, the latter indicating whether the step occurred in front of or behind the closest foot placement target. Errors are calculated separately for the straight and curved sections of the track, relative to the designated foot placement targets. In addition to the default measure (longitudinal distance from the foot to the target line), other error types can also be computed: lateral error (when the participant steps off the track) and total error (which combines longitudinal and lateral error, if present). A video of the step distribution, including the step error relative to the nearest target, can be generated for a specific trial by setting the video variable to 1 and selecting the desired trial.

- StepParametersHuxham: computes step length, step length variability, step width, and step width variability for each trial. These parameters are calculated separately for the straight and curved sections of the walking track.

- WalkingSpeed: determines walking speed, walking speed variability, stride duration, and stride duration variability. Calculations are based on pelvis marker displacement combined with step distribution.

- Head_back_angles: calculates head and trunk angles using motion capture markers placed on the pelvis, the neck (C7 vertebra), and the headset.

- Dist_gaze: provides a qualitative, purely descriptive estimate of how far ahead participants were looking, based on their height in combination with the head and trunk angles.

- Plotting_gait_metrics: creates box plots and runs statistics on gait metrics data (represented in Fig. 2a-d).

- pairplots: creates different seaborn pairplots and kernel density estimates to visualize gait metrics, as seen in Supplementary Fig. 5 and Fig. 2f-g.

- model_ranking_code: ridge regression models for wearable subset of data

- The required python package versions include matplotlib==3.10.6, numpy==1.26.4, pandas==2.3.2, seaborn==0.12.2, scipy==1.16.2, scikit-learn==1.3.1, and statsmodels==0.14.0

