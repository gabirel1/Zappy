##
## EPITECH PROJECT, 2021
## graphical
## File description:
## Makefile
##

build-mac:
	sudo $(UNITY_PATH) -quit -batchmode -projectPath ./ -buildOSXUniversalPlayer "../../Graphical_OSXBuild/Zappy.dmg"

build-linux:
	sudo $(UNITY_PATH) -quit -batchmode -projectPath ./ -buildLinux64Player "../../Graphical_LinuxBuild/Zappy"

all:	build-mac	build-Linux

clean:
	$(RM) -rf ../../Graphical_OSXBuild
	$(RM) -rf ../../Graphical_LinuxBuild

fclean:	clean