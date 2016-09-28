# nevt_min : starting event number 
# nevt_max : ending event number
# nevt_max = -1 : loop until the end 
nevt_min='0'
nevt_max='2'

#channel selection chselect = 1-4
chselect='1' 

outputDir='FitAnaResult'

# anafitt.cc(int nevt_min = 0, int nevt_max = 20, int chselect = 1, TString inputfile = "filename")


root -l 'anafitt.C+('$nevt_min', '$nevt_max', '$chselect')'
