# G4Canberra

A Geant4 implementation of the Mirion Canberra ReGe Detector + Cryo Pulse 5 Cooler.

## Detector Implementation
The Detector geometry was reconstructed using a CAD software starting from the following resources:
1. Cryo Pulse 5 Datasheet [here](docs/cryo-pulse_5_plus_spec_sheet.pdf).
2. HPGe ReGe Detector Geometry Datasheet.

Below are shown two views of the detector assembly.
<figure>
<p float="left">
<img src="docs/canberra_cryo_5_plus_sezione.jpg"  width = "300" /><img src="docs/canberra_cryo_5_plus.jpg" width = "300" />
</p>
<figcaption><p> &emsp;&emsp;&emsp;&emsp;(a) Side view &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;(b) Front View<p></figcaption>
</figure>

The conversion from ASCII STL format (inside Geometry/CanberraHPGe) to GDML is performed using the [CADMesh](https://github.com/christopherpoole/CADMesh) Library.

<figure>
<img src="docs/geant4_canberra_explodet.png"  width = "400"/>
<figcaption><p>&emsp; Exploded view of GDML implementation</p></figcaption>
</figure>

