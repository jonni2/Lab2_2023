void AnalysisRoofit(TString path = "Data/Muon_Data/R3_background_P1_ns.csv") {
    
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


void AnalysisRoofit2(){

    RooRealVar t("t", "t", 0, 16000);
    t.setBins(80);

    RooRealVar tau0("tau0", "#tau_{0}", 2200, 2000, 2500);
    RooFormulaVar rate0("rate0", "rate", "-1/tau0", RooArgSet(tau0));
    RooRealVar tau_mu("tau_mu", "#tau_{#mu}", 200, 100, 500);
    RooFormulaVar rate_mu("rate_mu", "rate", "-1/tau_mu", RooArgSet(tau_mu));
    RooConstVar R("R", "R", 1.21);
    RooFormulaVar R1("R1", "1/R", "1/R", RooArgSet(R));
    
    RooRealVar b("b", "b", 1, 0, 50);
    // RooUniform bkg("b", "b", t);
    RooPolynomial bkg("bkg", "bkg", b);

    RooExponential e0("e0", "e0", t, rate0);
    RooExponential e_mu("e_mu", "e_mu", t, rate_mu);
    // RooProdPdf e_muR("e_muR", "e_muR", RooArgList(e_mu, R1)); 

    // RooConstVar frac("frac", "Fraction", 0.5, 0, 1);
    RooAddPdf model0("model0", "model0", RooArgList(e0, e_mu), RooArgList(R1));
    

    RooRealVar nsig("nsig", "nsig", 300, 0, 10000);
    RooRealVar nbkg("nsig", "nsig", 10, 0, 100);
    RooAddPdf model("model", "model", RooArgList(bkg, model0), RooArgList(nbkg, nsig));

    //load unbinned dataset
    RooDataSet* data = RooDataSet::read("Data/Muon_Data/R3_data_P1_ns.csv", t);


    double tmin = 20;
    double tmax = 10000;
    //RooConstVar tmin ("tmin", "tmin", 20);
    //RooConstVar tmax ("tmax", "tmax", 10000);
    RooDataSet* dataRange = (RooDataSet*) data->reduce(RooFit::Range(tmin, tmax));


    RooPlot* frame = t.frame();


    //plot
    model.fitTo(*data);
    data->plotOn(frame);
    model.plotOn(frame); // always before fitTo
    frame->Draw();



}
