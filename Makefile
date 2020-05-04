# Fichier makefile pour projet termite
######################################

# Quelques variables de configuration du compilateur
####################################################
# Le compilateur Ã  utiliser
CXX = g++
# Les options du compilateur
CXXFLAGS = -Wall -std=c++11 -g
# Des options supplémentaires pour la compilation avec la SFML
SFOPT = -lsfml-graphics -lsfml-window -lsfml-system
# Le chemin vers le dossier où a lieu la compilation
DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
# Le chemin du dossier contenant les fichiers relatifs aux classes Bouton/bouton
BOUTON = $(DIR)Bouton/

# Les programmes principaux
###########################
# On donne le fichier .cpp et la liste des fichiers .o qu'ils utilisent

projet: projet.cpp coord.o grille.o termite.o # Ã  complÃ©ter...
testcoord: testcoord.cpp coord.o
testgrille: testgrille.cpp grille.o coord.o
testtermite: testtermite.cpp termite.o grille.o coord.o
gui: gui.cpp gui.o bouton_herit.o bouton.o termite.o grille.o coord.o
	$(CXX) $(CXXFLAGS) gui.o bouton_herit.o bouton.o termite.o grille.o coord.o -o gui $(SFOPT)
# Ã  complÃ©ter...

# Les diffÃ©rents composants
###########################
# on donne le fichier .cpp ainsi que la liste
# des fichiers .hpp dont ils dÃ©pendent

coord.o: coord.cpp coord.hpp
grille.o: grille.cpp grille.hpp coord.hpp
termite.o: termite.cpp termite.hpp grille.hpp coord.hpp
bouton.o: $(BOUTON)bouton.cpp $(BOUTON)bouton.hpp
	$(CXX) $(CXXFLAGS) -c $(BOUTON)bouton.cpp $(BOUTON)bouton.hpp
bouton_herit.o: $(BOUTON)bouton_herit.cpp $(BOUTON)bouton_herit.hpp $(BOUTON)bouton.hpp
	$(CXX) $(CXXFLAGS) -c $(BOUTON)bouton_herit.cpp $(BOUTON)bouton_herit.hpp $(BOUTON)bouton.hpp
gui.o: gui.cpp $(BOUTON)bouton_herit.hpp termite.hpp grille.hpp coord.hpp
	$(CXX) $(CXXFLAGS) -c $(DIR)gui.cpp $(BOUTON)bouton_herit.hpp termite.hpp

clean:
	rm -f projet testgrille testcoord testtermite gui *.o
fullClean:
	rm -f projet testgrille testcoord testtermite gui *.o *.gch
	rm -f $(BOUTON)*.o $(BOUTON)*.gch
chemin:
	echo $(DIR)
# Attention dans la ligne ci-dessus il faut Ã©crire
# un seul caractÃ¨re de tabulation et pas 8 espaces.
