/*
    - Alessandro Mancini - Project for the course "Statistical Data Analysis for Nuclear and Subnuclear Physics", A. A. 2022-23
  
    * This project aims to study some data collected for the course of "Laboratory of Nuclear and Subnuclear Physics 2" in which the muon mean lifetime was studied.
    
    * The dataset consists of decay times of muons in the range [0, 16000] ns which have been collected by an experimental appartus composed of scintillators and PMTs.
    
    * The dataset has been fitted with the following model:
    
    f(t) = fsig(t) + b = (exp(-t/tau0) + 1/R*exp(-t/tau_mu)) + b
    
    where fsig(t) is the typical decay law for radioactive particles, R is the muon atmospheric ratio and b is a uniform background component present in the experiment. tau0 is the mean lifetime of muon decay, while tau_mu is the mean lifetime of muon capture: a phenomenon that happens when negative muons interact with the iron slabs used in the apparatus.

 
    References:
    [1] Bahmanabadi et al. "The charge ratio of the atmospheric muons at low energy", Phys. Rev. D, 2006
    [2] 
 
 
 
 
*/


// Function fitting
void AnalysisRoofit(TString path = "Data/Muon_Data/Reduced_Data/R3_data_P1_reduced.csv"){

    // Observable of the experiment: muon decay time //////////////////////
    RooRealVar t("t", "t", 200, 16000, "ns");
    t.setBins(79);

    // Parameters of the model ///////////////////////////////////////////
    // tau0 = mean lifetime of muon decay
    RooRealVar tau0("tau0", "#tau_{0}", 2200, 2000, 2500);
    RooFormulaVar rate0("rate0", "rate", "-1/tau0", RooArgSet(tau0));
    
    // tau_mu = mean lifetime of negative muon = decay + capture
    RooRealVar tau_mu("tau_mu", "#tau_{#mu}", 200, 100, 500);
    RooFormulaVar rate_mu("rate_mu", "rate", "-1/tau_mu", RooArgSet(tau_mu));
    
    // Atmospheric muon ratio R = 1.21 [1]
    RooConstVar R("R", "R", 1.21);
    RooFormulaVar R1("R1", "1/R", "1/R", RooArgSet(R));
    
    // PDFs of the model /////////////////////////////////////////////////
    // Expression of the signal pdf
    RooFormulaVar exp("exp", "e^(-t/tau0)+R1*e^(-t/tau_mu)", RooArgList(t, tau0, R1, tau_mu));
    // Signal pdf = sum of the two exponentials
    RooGenericPdf sig("sig", "sig", "@0", RooArgList(exp));
    
    // Background uniform pdf
    RooUniform bkg("bkg", "bkg", t);


    // Using numbers of events of sig and bkg to define extended Likelihood
    RooRealVar nsig("nsig", "nsig", 1000, 0, 16000);
    RooRealVar nbkg("nbkg", "nbkg", 100, 0, 16000);
    
    
    // Total pdf model of the experiment
    RooAddPdf model("model", "model", RooArgList(sig, bkg), RooArgList(nsig, nbkg));
    
    //load unbinned dataset //////////////////////////////////////////////
    RooDataSet data = *RooDataSet::read(path, t);

    // Frame for plotting ////////////////////////////////////////////////
    RooPlot* frame = t.frame(RooFit::Title("Muon decay times"));

    // Fitting model to data /////////////////////////////////////////////
    model.fitTo(data, RooFit::Range(200, 16000));

    // Plot data and model on the same frame
    data.plotOn(frame);
    model.plotOn(frame);
    
    // Plotting components of the model
    model.plotOn(frame, RooFit::Components("sig"), RooFit::LineStyle(kDashed));
    model.plotOn(frame, RooFit::Components("bkg"), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
    
    TCanvas* c = new TCanvas("c", "Fit");
    c->SetLogy(); // Visualize log scale in y
    c->cd();
    frame->Draw();
    
    
    // Creating the -log(LIKELIHOOD) function ////////////////////////////
    RooAbsReal* nll = model.createNLL(data);
    RooMinuit m(*nll); // Creating Minuit object
    
    // Additional visualization of minimization procedure
    // m.setVerbose(kTRUE);
    
    // Run the minimization algorithms of RooMinuit //////////////////////
    // Run Migrad algorithm to find minimum of -log(Lik)
    m.migrad();
    
    // Output file to store fit results
    std::ofstream os{"MuonDecay.txt"};
    
    // Print result from Migrad
    os << "Migrad: \n\ttau0: ";
    tau0.printValue(os);
    os << "\n\ttau_mu: ";
    tau_mu.printValue(os);
    os << "\n\n";
    
    // Run Hesse to find (symmetric) errors from parabolic Likelihood
    m.hesse();
    
    // Print result from Hesse
    os << "Hesse: \n\ttau0: ";
    tau0.printValue(os);
    os << "\n\ttau_mu: ";
    tau_mu.printValue(os);
    os << "\n\n";
    
    // Run Minos to find (asymmetric) errors with -ln(Lmax)+1/2
    m.minos();
    
    // Print result from Minos
    os << "Minos: \n\ttau0: ";
    tau0.printValue(os);
    os << "\n\ttau_mu: ";
    tau_mu.printValue(os);
    os << "\n\n";
    
    // Save fit results
    RooFitResult* result = m.save();
    
    // Print fit results
    result->printMultiline(os, 0, kTRUE);
    
    os.close();
    
    // Drawing ///////////////////////////////////////////////////////////
    // Canvas to draw the Contour Likelihood plot
    TCanvas* c2 = new TCanvas("c2", "c2");
    
    // Make Likelihood Contour plot of the two mean lifetimes
    RooPlot* frame_contour = m.contour(tau0, tau_mu, 1, 2);
    frame_contour->SetTitle("Contour plot, #tau_{0} vs #tau_{#mu}");
    
    c2->cd();
    frame_contour->Draw();
    
    // Plot tau0 Likelihood
    RooPlot* frame2 = tau0.frame(RooFit::Title("Likelihood #tau_{0}"));
    nll->plotOn(frame2, RooFit::ShiftToZero());
    
    // Plot tau_mu Likelihood
    RooPlot* frame3 = tau_mu.frame(RooFit::Title("Likelihood #tau_{#mu}"));
    nll->plotOn(frame3, RooFit::ShiftToZero());
    
    // Plot nsig Likelihood
    RooPlot* frame4 = nsig.frame(RooFit::Title("Likelihood nsig"));
    nll->plotOn(frame4, RooFit::ShiftToZero());
    
    // Plot nbkgs Likelihood
    RooPlot* frame5 = nbkg.frame(RooFit::Title("Likelihood nbkg"));
    nll->plotOn(frame5, RooFit::ShiftToZero());
    
    // Draw all the frames in TCanvas
    TCanvas* c3 = new TCanvas("c3", "c3");
    c3->Divide(2,2);
    c3->cd(1);
    frame2->Draw();    
    c3->cd(2);
    frame3->Draw();
    c3->cd(3);
    frame4->Draw();
    c3->cd(4);
    frame5->Draw();

}
