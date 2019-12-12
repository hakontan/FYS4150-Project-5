#!/bin/bash
cd src

echo "Compile? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  make clean
  make rmexecs
  make
fi

echo "Process data? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pipenv run python process_planet_data.py
  pipenv run python process_planet_data.py Sun Earth Jupiter
  pipenv run python process_planet_data.py Sun Mercury Venus Earth Roadster Mars Jupiter Saturn Neptune Uranus Pluto
  pipenv run python process_planet_data.py Sun Mercury
fi

echo "Generate results task b and c? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  mkdir -p datafiles/filestaskc
  ./outputtaskc.out sunearth_custom1
fi

echo "Run tests task b and c? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pytest -v
fi

echo "Generate plots for task b and c? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pipenv run python plot_taskb.py
  #python plot_sun_earth.py Sun Earth
  pipenv run python plot_energies_and_angmom.py
fi

echo "Generate results task d? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  mkdir -p datafiles/filestaskd
  ./outputtaskd.out
fi

echo "Plot results task d? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pipenv run python plot_taskd.py
fi

echo "Generate results task e? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  mkdir -p datafiles/filestaske
  ./outputtaske.out
fi

echo "Plot results task e? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pipenv run python plot_taske.py
fi

echo "Generate results task f? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  mkdir -p datafiles/filestaskf
  ./outputtaskf.out Sun Mercury Venus Earth Roadster Mars Jupiter Saturn Neptune Uranus Pluto
fi

echo "Plot results task f? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pipenv run python plot_taskf.py
fi

echo "Calculate task g? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  mkdir -p datafiles/filestaskg
  ./outputtaskg Sun Mercury
fi

echo "Compile report? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  cd ../doc/
  pdflatex -synctex=1 -interaction=nonstopmode CompPhysProj5.tex
  bibtex CompPhysProj5.aux
  pdflatex -synctex=1 -interaction=nonstopmode CompPhysProj5.tex
  bibtex CompPhysProj5.aux
  pdflatex -synctex=1 -interaction=nonstopmode CompPhysProj5.tex
fi
