# DE1-SoC ADC to FPGA LED Bar Controller ⚪ ⚪ 🔴 🔴

An embedded C application for the Terasic DE1-SoC development board that reads continuous analog values from an external ADC (MCP3201) via Linux IIO sysfs and drives a bar-graph display on 10 FPGA user LEDs.

---

## Architecture & Hardware

* **Development Board:** DE1-SoC (Cyclone V SoC)
* **A/D Converter:** MCP3201 (interfaced via SPI)
* **Output:** 10x FPGA LEDs (mapped via sysfs / GPIO / IIO)
* **Environment:** Embedded Linux built using Buildroot

To be added...
