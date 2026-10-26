# Alpha Spectroscopy Data Analysis

## Context
This repository contains the data analysis scripts and computational routines developed for the **Alpha Spectroscopy** laboratory experiment, part of the Nuclear and Subnuclear Physics course. 

The experiment investigates the physics of alpha decay and the interaction of heavy charged particles with matter. The experimental setup involves a Silicon PIN photodiode detector placed inside a vacuum chamber, coupled with an amplification chain and a Multi-Channel Analyzer (MCA). The provided code handles the processing of the digital spectra acquired during the experimental sessions, implementing automated fitting procedures, statistical tests (such as chi-square and Z-tests), and error propagation.

## Objectives
The primary goals of the analytical code are to extract physical observables from the raw MCA spectra without hardcoding the final numerical outcomes. The scripts are designed to sequentially tackle the following experimental objectives:

* **Electronic Chain Linearity:** Verify the linear response of the amplification and analog-to-digital conversion systems using simulated pulse generator signals.
* **MCA Energy Calibration:** Establish the channel-to-energy conversion relationship by fitting the primary emission peaks of a triple alpha source (239Pu, 241Am, 244Cm).
* **Energy Loss in Matter (Mylar):** Evaluate the energy degradation and straggling effects of 241Am alpha particles passing through varying thicknesses of Mylar absorbers.
* **Solid Angle Acceptance:** Analyze the event counting rate as a function of the source-to-detector distance to model the geometric acceptance and its deviation from a simple 1/r^2 behavior at close ranges.
* **Alpha Particle Range in Air:** Determine the equivalent range of alpha particles in air at standard temperature and pressure (STP) by systematically increasing the pressure inside the vacuum chamber and modeling the rate drop-off.
* **Branching Ratios Evaluation:** Estimate the decay fractions for the secondary and tertiary emission peaks of 241Am by applying multi-component Crystal Ball function fits to handle peak asymmetries and energy straggling tails.
* **232Th Decay Chain Analysis:** Process a long-acquisition spectrum of Thorium-232 to extract the alpha decay energies, sequentially reconstruct the atomic masses of the daughter isotopes, and calculate the average Binding Energy per nucleon (B/A).
