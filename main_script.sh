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
  python process_planet_data.py Sun Earth Jupiter
fi

echo "Generate results task c? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  ./outputtaskc.out Sun Earth
fi

echo "Run tests? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  pytest -v
fi

echo "Generate results task d? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  ./outputtaskd.out
fi

echo "Generate results task e? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  ./outputtaske.out
fi

echo "Generate results task f? (y/n)"
read yn
if [ "$yn" == "y" ]
then
  ./outputtaskf.out 
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
