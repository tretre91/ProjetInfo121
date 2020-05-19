# Fichier makefile pour projet termite
######################################

# Quelques variables de configuration du compilateur
####################################################
# Le compilateur Ã  utiliser
CXX = g++
# Les options du compilateur
CXXFLAGS = -Wall -std=c++11 -g -O3
# Des options supplémentaires pour la compilation avec la SFML
SFOPT = -lsfml-graphics -lsfml-window -lsfml-system

# Les programmes principaux
###########################
# On donne le fichier .cpp et la liste des fichiers .o qu'ils utilisent

projet: projet.cpp coord.o grille.o termite.o # Ã  complÃ©ter...
testcoord: testcoord.cpp coord.o
testgrille: testgrille.cpp grille.o coord.o
testtermite: testtermite.cpp termite.o grille.o coord.o
gui: gui.cpp gui.o termite.o grille.o coord.o
	$(CXX) $(CXXFLAGS) gui.o termite.o grille.o coord.o -o gui $(SFOPT)
# Ã  complÃ©ter...

# Les diffÃ©rents composants
###########################
# on donne le fichier .cpp ainsi que la liste
# des fichiers .hpp dont ils dÃ©pendent

coord.o: coord.cpp coord.hpp
grille.o: grille.cpp grille.hpp coord.hpp
termite.o: termite.cpp termite.hpp grille.hpp coord.hpp
gui.o: gui.cpp termite.hpp grille.hpp coord.hpp

clean:
	rm -f projet testgrille testcoord testtermite gui *.o
fullClean:
	rm -f projet testgrille testcoord testtermite gui *.o *.gch

# Attention dans la ligne ci-dessus il faut Ã©crire
# un seul caractÃ¨re de tabulation et pas 8 espaces.
