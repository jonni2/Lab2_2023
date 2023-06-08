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
    // RooConstVar R("R", "R", 1.21);
    // RooFormulaVar R1("R1", "1/R", "1/R", RooArgSet(R));
    
    // RooRealVar b("b", "b", 1, 0, 50);
    RooUniform bkg("bkg", "bkg", t);
    // RooPolynomial bkg("bkg", "bkg", b);

    RooExponential e0("e0", "e0", t, rate0);
    RooExponential e_mu("e_mu", "e_mu", t, rate_mu);
    // RooProdPdf e_muR("e_muR", "e_muR", RooArgList(e_mu, R1)); 

    // RooFormulaVar e_muR("model0", "@0*@1", RooArgList(R1, e_mu));
    
    // RooRealVar f0("f0", "Fraction of e0", 0.5, 0, 1);
    // RooRealVar fmu("fmu", "Fraction of e_mu", 0.5, 0, 1);
    // RooGenericPdf model0("model0", "model0", "@0+@1", RooArgList(e_muR, e0));
    

    // Using Number of EVENTS
    RooRealVar n0("n0", "n0", 1000, 0, 16000);
    RooRealVar n_mu("n_mu", "n_mu", 800, 0, 16000);
    RooRealVar nbkg("nbkg", "nbkg", 100, 0, 16000);
    
    // Using FRACTIONS
    // RooRealVar f0("f0", "f0", 0.8, 0, 1);
    // RooRealVar f_mu("f_mu", "f_mu", 0.2, 0, 1);
    
    RooAddPdf model("model", "model", RooArgList(e0, e_mu, bkg), RooArgList(n0, n_mu, nbkg));
    // RooAddPdf model("model", "model", RooArgList(model0, bkg), RooArgList(nsig, nbkg));

    //load unbinned dataset
    RooDataSet data = *RooDataSet::read("Data/Muon_Data/R3_data_P1_ns.csv", t);


    // double tmin = 20;
    // double tmax = 10000;
    //RooConstVar tmin ("tmin", "tmin", 20);
    //RooConstVar tmax ("tmax", "tmax", 10000);
    // RooDataSet* dataRange = (RooDataSet*) data->reduce(RooFit::Range(tmin, tmax));


    RooPlot* frame = t.frame(RooFit::Title("Muon decay times"));


    //plot
    model.fitTo(data);
    data.plotOn(frame);
    model.plotOn(frame); // always before fitTo
    // e0.plotOn(frame,RooFit::LineColor(kRed));
    // e_mu.plotOn(frame,RooFit::LineColor(kOrange));
    // bkg.plotOn(frame, RooFit::LineColor(kBlack));
    frame->Draw();
    
    // Creating the LIKELIHOOD
    RooAbsReal* nll = model.createNLL(data);
    RooMinuit m(*nll);
    m.migrad();
    
    RooPlot* frame_contour = m.contour(tau0, tau_mu, 1, 2);
    frame_contour->SetTitle("Contour plot, #tau_{0} vs #tau_{#mu}");
    frame_contour->Draw();
    
    // RooPlot* frame_tau = tau0.frame();
    // nll->plotOn(frame_tau);
    // frame_tau->Draw();

}
