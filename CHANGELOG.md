<a name="0.7.0"></a>
# 0.7.0 (2016-01-10)


### Bug Fixes

* **$BlockDesigner:** fix bugs<View_Simulation> ([cd7b79d](https://github.com/twoblock/BlockDesigner/commit/cd7b79d))
* **$BlockDesigner:** remove all compile warning ([cb5a10c](https://github.com/twoblock/BlockDesigner/commit/cb5a10c))
* **$JNI:** fix JNI ( Handler_Command files ) ([908e0b4](https://github.com/twoblock/BlockDesigner/commit/908e0b4))
* **$JNI_Interface:** bug fix all script ([a4c58b2](https://github.com/twoblock/BlockDesigner/commit/a4c58b2))
* **$PlugIn:** move from local workspace ([b074026](https://github.com/twoblock/BlockDesigner/commit/b074026))

### Features

* **$BD_core:** add Simulation Thread, GUI Thread ([f46b695](https://github.com/twoblock/BlockDesigner/commit/f46b695))
* **$BD_core:** make BD_core base structure ([2be2ecf](https://github.com/twoblock/BlockDesigner/commit/2be2ecf))
* **$BD_core:** modify directory structure, Execution manager ([766bc66](https://github.com/twoblock/BlockDesigner/commit/766bc66))
* **$BlockDesigner:** commit initial Block Designer ([d448ee3](https://github.com/twoblock/BlockDesigner/commit/d448ee3))
* **$ExcutionManager:** add Excution Manager (/systemc-2.3.1_BD/src/BD_core/manager) ([b24c0fe](https://github.com/twoblock/BlockDesigner/commit/b24c0fe))
* **$gui:** add StartSimulationThreads function for JNI ([2842127](https://github.com/twoblock/BlockDesigner/commit/2842127))
* **$gui:** Merge branch 'feat-StartSimulationThreads' into develop ([8d3766b](https://github.com/twoblock/BlockDesigner/commit/8d3766b))
* **$JNIinterface:** complete BlockDesigner Simulation JNI interface ([1420458](https://github.com/twoblock/BlockDesigner/commit/1420458))
* **$libBD_sim.so:** add to JNI Method ([182df2f](https://github.com/twoblock/BlockDesigner/commit/182df2f))
* **$PlugIn:** last window commit ([62e136a](https://github.com/twoblock/BlockDesigner/commit/62e136a))
* **$PlugIn:** merge 'feat-linux-migration' ([6d5c2fb](https://github.com/twoblock/BlockDesigner/commit/6d5c2fb))
* **$PlugIn:** migrate to Linux development environment ([b57621e](https://github.com/twoblock/BlockDesigner/commit/b57621e))
* **$SimulationHandler:** add Simulation Handler ([1afb1ef](https://github.com/twoblock/BlockDesigner/commit/1afb1ef))
* **JNIinterface:** Merge branch 'feat-JNIinterface' into develop ([cee0001](https://github.com/twoblock/BlockDesigner/commit/cee0001))
* **release:** release v0.7.0 ([ce59547](https://github.com/twoblock/BlockDesigner/commit/ce59547))


### BREAKING CHANGES

* release:  user handle simulation control( Run, Stop, Step ) based on GUI

 - add BD_core in systemc library

 - add BD_plug_in for GUI

 - add JNI to communicate
   between Java( GUI thread ) and c++ ( simulation threads )



