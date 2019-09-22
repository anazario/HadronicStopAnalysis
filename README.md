# HadronicStopAnalysis
PHSX 861 Project - SUSY analysis design for top squark pair production in the all-hadronic final state.

## Run Instructions
```
git clone git@github.com:anazario/HadronicStopAnalysis.git
cd HadronicStopAnalysis
make -j4
```
### Produce reduced nTuple:
```
./reduceTuple.x -i INPUTFILE -s SAMPLENAME
```
### Make Plot:
```
./makePlots -i INPUTFILE
```
