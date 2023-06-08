// Background estimation
void AnalysisRoofit2(TString path = "Data/Muon_Data/R3_background_P1_ns.csv") {
    
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
void AnalysisRoofit(){

    RooRealVar t("t", "t", 0, 16000, "ns");
    t.setBins(80);

    RooRealVar tau0("tau0", "#tau_{0}", 2200, 2000, 2500);
    RooFormulaVar rate0("rate0", "rate", "-1/tau0", RooArgSet(tau0));
    RooRealVar tau_mu("tau_mu", "#tau_{#mu}", 200, 100, 500);
    RooFormulaVar rate_mu("rate_mu", "rate", "-1/tau_mu", RooArgSet(tau_mu));
    
    RooConstVar R("R", "R", 1.21);
    RooFormulaVar R1("R1", "1/R", "1/R", RooArgSet(R));
    
    RooFormulaVar exp("exp", "e^(-t/tau0)+R1*e^(-t/tau_mu)", RooArgList(t, tau0, R1, tau_mu));
    
    RooUniform bkg("bkg", "bkg", t);


    // Using Number of EVENTS
    // RooRealVar nsig("nsig", "nsig", 1000, 0, 16000);
    // RooRealVar nbkg("nbkg", "nbkg", 100, 0, 16000);
    
    // Using FRACTIONS
    RooRealVar fsig("nsig", "nsig", 0.1000, 0, 1);
    
    // Signal pdf = sum of the two exponentials
    RooGenericPdf sig("sig", "sig", "@0", RooArgList(exp));
    RooAddPdf model("model", "model", RooArgList(sig, bkg), RooArgList(fsig));
    
    //load unbinned dataset
    RooDataSet data = *RooDataSet::read("Data/Muon_Data/R3_data_P3_ns.csv", t);

    // Frame for plotting
    RooPlot* frame = t.frame(RooFit::Title("Muon decay times"));

    // Fitting model to data
    model.fitTo(data, RooFit::Range(200, 16000));

    // Plot data and model on the same frame
    data.plotOn(frame);
    model.plotOn(frame); // always before fitTo
    frame->Draw();
    
    
    // Creating the LIKELIHOOD
    RooAbsReal* nll = model.createNLL(data);
    RooMinuit m(*nll);
    m.migrad();
    
    RooPlot* frame_contour = m.contour(tau0, tau_mu, 1, 2);
    frame_contour->SetTitle("Contour plot, #tau_{0} vs #tau_{#mu}");
    frame_contour->Draw();
    

}
