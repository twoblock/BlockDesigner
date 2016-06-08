# Introduction

BlockDesigner is GUI simulation tool based on systemc, gtkwave

Systemc is hardware software co-simulation library based on CUI(command user interface). 
So this is useful for people who want to simulate hardware system with software.
But It is very difficult to analyze simulation information because systemc library is CUI 

To overcome this weakness, we tried to transform this library to GUI(graphic user interface).
As a result, we made a tool called BlockDesigner with GUI feature.

This tool have three features.

1. module wizard - user can make module fast that can be used for BlockDesigner.

2. platform manager - user can connect modules without considering all signals because this tool provide AHB binding feature.

3. simulator - user can control simulation state(run, stop, step) and analyze all information that is generated from simulation. 

# Feature 

#### 1. module wizard - make BlockDesigner module

	write component name, select location and module type
![modulewizard](/image/modulewizard1.png)

	make module ports
![modulewizard](/image/modulewizard2.png)

	make module registers
![modulewizard](/image/modulewizard3.png)

	make module parameters
![modulewizard](/image/modulewizard4.png)

	make module process
![modulewizard](/image/modulewizard5.png)

	define sensitivity list
![modulewizard](/image/modulewizard6.png)

#### 2. platform manager - connect modules

	load and connect modules, memory map setting
![platformmanager](/image/platformmanager.png)

#### 3. simulator - simulate system

	register view
![simulator](/image/registerview.png)

	gtkwave signal view, memory view
![simulator](/image/gtkwavememoryview.png)

	assembly code view, sotware function profiling view
![simulator](/image/softwareprofilingview.png)

	call stack view
![simulator](/image/callstack.png)

# Requirement

linux ubuntu 12.04 

Eclipse IDE for java EE Developers( mars )
[Download](http://www.eclipse.org/downloads/packages/eclipse-ide-java-ee-developers/mars2)

jdk 1.8
[Download](http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)

jre 1.8
[Download](http://www.oracle.com/technetwork/java/javase/downloads/jre8-downloads-2133155.html)

gtkwave

	sudo apt-get install gtkwave

verilator
[Download](http://www.veripool.org/projects/verilator/wiki/Installing)

	sudo apt-get install make autoconf g++ flex bison

	unset VERILATOR_ROOT

	tar xvzf verilator*.t*gz

	cd verilator*

	./configure

	make

	sudo make install

# Install

	mkdir ~/workspace

	git clone https://github.com/twoblock/BlockDesigner.git

	cd ~/workspace/BlockDesigner/testCommand

	source EntireInstall.sh

	mv ~/workspace/BlockDesigner/BlockDesigner_1.0.0.jar /*your_eclipse_path*/eclipse/plugins/

# Execution

	source ~/workspace/BlockDesigner/TestPlatform/sc_main/systemc.csh 
	source ~/workspace/BlockDesigner/TestPlatform/sc_main/scv.csh

	eclipse
