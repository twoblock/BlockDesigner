<a name="0.2.0"></a>
# [0.2.0](https://github.com/twoblock/BlockDesigner/compare/v0.1.0...v0.2.0) (2016-01-26)


### Bug Fixes

* **$gui/test.h:** add the 'fstream' header file ([72458b1](https://github.com/twoblock/BlockDesigner/commit/72458b1))
* **$PMModuleListManager:** fix segmentation fault ([124964d](https://github.com/twoblock/BlockDesigner/commit/124964d))
* **$PMModuleListManager:** merge to fix this manager ([501974a](https://github.com/twoblock/BlockDesigner/commit/501974a))
* **$SoftwareProfiler:** fix the warning code ([48b75b9](https://github.com/twoblock/BlockDesigner/commit/48b75b9))

### Features

* **$BDDI:** design parameter APIs ([d8efd66](https://github.com/twoblock/BlockDesigner/commit/d8efd66))
* **$BDDI:** make BDDI base ([607500a](https://github.com/twoblock/BlockDesigner/commit/607500a))
* **$BDDI:** make set/get register function ([9229744](https://github.com/twoblock/BlockDesigner/commit/9229744))
* **$BDDI:** merge BDDI base ([b6a15d2](https://github.com/twoblock/BlockDesigner/commit/b6a15d2))
* **$BDDI:** merge BDDI functions ([c6d7b90](https://github.com/twoblock/BlockDesigner/commit/c6d7b90))
* **$BDDI:** merge BDDI parameter API ([3ca3944](https://github.com/twoblock/BlockDesigner/commit/3ca3944))
* **$PlatformAPI:** load module and make module info json file ([477af82](https://github.com/twoblock/BlockDesigner/commit/477af82))
* **$PlatformManagerAPI:** merge PlatformManagerAPI ([7368c50](https://github.com/twoblock/BlockDesigner/commit/7368c50))
* **$PMModuleListManager:** make this manager to load sc_module and manager them ([03eeeda](https://github.com/twoblock/BlockDesigner/commit/03eeeda))
* **$PMModuleListManager:** merge this manager ([1d78de0](https://github.com/twoblock/BlockDesigner/commit/1d78de0))
* **$version:** release v.0.2.0 ([ce546be](https://github.com/twoblock/BlockDesigner/commit/ce546be))



<a name="0.1.0"></a>
# 0.1.0 (2016-01-10)


### Bug Fixes

* **$BD_core:** fix makefile to make libBD_sim.so ([8ba69b9](https://github.com/twoblock/BlockDesigner/commit/8ba69b9))
* **$BlockDesigner:** fix bugs<View_Simulation> ([cd7b79d](https://github.com/twoblock/BlockDesigner/commit/cd7b79d))
* **$BlockDesigner:** remove all compile warning ([cb5a10c](https://github.com/twoblock/BlockDesigner/commit/cb5a10c))
* **$gtkwave:** complete gtkwave interactive mode ([4dd2941](https://github.com/twoblock/BlockDesigner/commit/4dd2941))
* **$gtkwave:** merge gtkwave interactive mode feature ([4d35a3c](https://github.com/twoblock/BlockDesigner/commit/4d35a3c))
* **$gtkwave:** support gtkwave interactive mode ([cd3d93e](https://github.com/twoblock/BlockDesigner/commit/cd3d93e))
* **$JNI:** fix JNI ( Handler_Command files ) ([908e0b4](https://github.com/twoblock/BlockDesigner/commit/908e0b4))
* **$JNI_Interface:** bug fix all script ([a4c58b2](https://github.com/twoblock/BlockDesigner/commit/a4c58b2))
* **$PlugIn:** move from local workspace ([b074026](https://github.com/twoblock/BlockDesigner/commit/b074026))

### Features

* **$BD_core:** add Simulation Thread, GUI Thread ([f46b695](https://github.com/twoblock/BlockDesigner/commit/f46b695))
* **$BD_core:** make BD_core base structure ([2be2ecf](https://github.com/twoblock/BlockDesigner/commit/2be2ecf))
* **$BD_core:** modify directory structure, Execution manager ([766bc66](https://github.com/twoblock/BlockDesigner/commit/766bc66))
* **$BlockDeisnger:** fix libBD_sim.so, add test platform ([b4540b6](https://github.com/twoblock/BlockDesigner/commit/b4540b6))
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
* **release:** release v0.7.0 ([5b24ab2](https://github.com/twoblock/BlockDesigner/commit/5b24ab2))


### BREAKING CHANGES

* release:  user handle simulation control( Run, Stop, Step ) based on GUI

 - add BD_core in systemc library

 - add BD_plug_in for GUI

 - add JNI to communicate
   between Java( GUI thread ) and c++ ( simulation threads )



