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
  pytest
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
