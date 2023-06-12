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

// Background estimation
void AnalysisBackground(TString path = "Data/Muon_Data/R3_background_P1_ns.csv") {
    
    gStyle->SetOptStat(10);
    
    RooRealVar t("t", "t", 0, 16000);
    t.setBins(50);
    
    
    RooDataSet data = *RooDataSet::read(path, t);
    
    // RooRealVar b("b", "b", 15, 0, 30);
    // RooPolynomial p0("p", "p", t, RooArgSet());
    RooUniform p0("p0", "p0", t);
    
    p0.fitTo(data);
    
    RooPlot* frame = t.frame(RooFit::Title("Background estimation"));
    
    data.plotOn(frame);
    p0.plotOn(frame);
    
    frame->Draw();
    
}

// Function fitting
void AnalysisRoofit(TString path = "Data/Muon_Data/R3_data_P1_ns.csv"){

    RooRealVar t("t", "t", 0, 16000, "ns");
    t.setBins(80);

    // Parameters of the model
    // tau0 = mean lifetime of muon decay
    RooRealVar tau0("tau0", "#tau_{0}", 2200, 2000, 2500);
    RooFormulaVar rate0("rate0", "rate", "-1/tau0", RooArgSet(tau0));
    
    // tau_mu = mean lifetime of negative muon capture
    RooRealVar tau_mu("tau_mu", "#tau_{#mu}", 200, 100, 500);
    RooFormulaVar rate_mu("rate_mu", "rate", "-1/tau_mu", RooArgSet(tau_mu));
    
    // Atmospheric muon ratio R = 1.21 [1]
    RooConstVar R("R", "R", 1.21);
    RooFormulaVar R1("R1", "1/R", "1/R", RooArgSet(R));
    
    // Expression of the signal pdf
    RooFormulaVar exp("exp", "e^(-t/tau0)+R1*e^(-t/tau_mu)", RooArgList(t, tau0, R1, tau_mu));
    
    // Background uniform pdf
    RooUniform bkg("bkg", "bkg", t);


    // Using numbers of events of sig and bkg
    // RooRealVar nsig("nsig", "nsig", 1000, 0, 16000);
    // RooRealVar nbkg("nbkg", "nbkg", 100, 0, 16000);
    
    // Using fraction of sig
    RooRealVar fsig("fsig", "fsig", 0.9, 0, 1);
    
    // Signal pdf = sum of the two exponentials
    RooGenericPdf sig("sig", "sig", "@0", RooArgList(exp));
    
    // Total pdf model of the experiment
    RooAddPdf model("model", "model", RooArgList(sig, bkg), RooArgList(fsig));
    
    //load unbinned dataset
    RooDataSet data = *RooDataSet::read(path, t);

    // Frame for plotting
    RooPlot* frame = t.frame(RooFit::Title("Muon decay times"));

    // Fitting model to data
    model.fitTo(data, RooFit::Range(200, 16000));

    // Plot data and model on the same frame
    TCanvas* c = new TCanvas("c", "Fit");
    c->SetLogy();
    data.plotOn(frame);
    model.plotOn(frame); // always before fitTo
    c->cd();
    frame->Draw();
    
    
    // Creating the LIKELIHOOD function
    RooAbsReal* nll = model.createNLL(data);
    RooMinuit m(*nll);
    
    // m.setVerbose(kTRUE);
    
    m.migrad();
    m.hesse();
    
    TCanvas* c2 = new TCanvas("c2", "c2");
    
    RooPlot* frame_contour = m.contour(tau0, tau_mu, 1, 2);
    frame_contour->SetTitle("Contour plot, #tau_{0} vs #tau_{#mu}");
    
    c2->cd();
    frame_contour->Draw();
    
    
    RooPlot* frame2 = tau0.frame(RooFit::Title("Likelihood #tau_{0}"));
    nll->plotOn(frame2, RooFit::ShiftToZero());
    
    RooPlot* frame3 = tau_mu.frame(RooFit::Title("Likelihood #tau_{#mu}"));
    nll->plotOn(frame3, RooFit::ShiftToZero());
    
    RooPlot* frame4 = fsig.frame(RooFit::Title("Likelihood fsig"));
    nll->plotOn(frame4, RooFit::ShiftToZero());
    
    TCanvas* c3 = new TCanvas("c3", "c3");
    c3->Divide(3,1);
    c3->cd(1);
    frame2->Draw();    
    c3->cd(2);
    frame3->Draw();
    c3->cd(3);
    frame4->Draw();



}
