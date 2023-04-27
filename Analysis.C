// Root Program to perform data analysis

/*
 
 Experimental apparatus:
 
 ------------- P3
 ------------- P2
############### Fe
 ------------- P1
 
 
*/


// function to plot HV scan
void Plot_HV(TString path) {
    
    TGraph* g1 = new TGraph(path, "%lg %lg", ",");
    
    g1->SetTitle("High Voltage scan, PMT 7-8; PMTs Voltage (V); Counts");
    g1->SetMarkerStyle(7);
    g1->SetMarkerColor(kBlue);
    g1->SetLineColor(kBlue);
    
    TGraph* g2 = new TGraph(path, "%lg %*lg %lg", ",");
    g2->SetMarkerStyle(7);
    g2->SetMarkerSize(2);
    g2->SetMarkerColor(kRed);
    g2->SetLineColor(kRed);
    
    TLegend* leg = new TLegend(.1, .7, .4, .9);
    leg->AddEntry(g1, "PMT 7 single counts");
    leg->AddEntry(g2, "PMT 8 single counts");
    
    TCanvas* c = new TCanvas("c", "HV scan");
    c->cd();
    g1->Draw("APL");
    g2->Draw("PL,SAME");
    leg->Draw("SAME");
    
}

void Plot_Thr(TString path) {
    TGraph* g1 = new TGraph(path, "%lg %lg", ",");
    
    g1->SetTitle("Threshold scan, PMT 7-8; Threshold Voltage (mV); Counts");
    g1->SetMarkerStyle(7);
    g1->SetMarkerColor(kBlue);
    g1->SetLineColor(kBlue);
    
    TGraph* g2 = new TGraph(path, "%lg %*lg %lg", ",");
    g2->SetMarkerStyle(7);
    g2->SetMarkerSize(2);
    g2->SetMarkerColor(kRed);
    g2->SetLineColor(kRed);
    
    TLegend* leg = new TLegend(.1, .7, .4, .9);
    leg->AddEntry(g1, "PMT 7 single counts");
    leg->AddEntry(g2, "PMT 8 single counts");
    
    TCanvas* c = new TCanvas("c", "Thr scan");
    c->cd();
    g1->Draw("APL");
    g2->Draw("PL,SAME");
    leg->Draw("SAME");
}

void Fit_sig(TString path) {
    gStyle->SetOptFit(1111);
    
    TTree* t = new TTree("t", "Tree");
    t->ReadFile(path, "N_event/D:t_trig:tP1:tP2:tP3");
    
    TH1F* hP1 = new TH1F("hP1", "times in P1", 100, 0., 3500.);
    t->Draw("tP2 >> hP1");

    hP1->SetTitle("Times in P1; time (ticks... FARE CALIBRAZ); Counts");
    hP1->GetXaxis()->SetRange(0.,4000.);
    hP1->SetMaximum(400);
    
    TF1* f_exp = new TF1("f_exp", "[0]*e^(-x/[1])+[2]");
    f_exp->SetParNames("A","tau","b");
    f_exp->SetParameters(300, 2200, 0.5);
    
    hP1->Fit("f_exp", "", "", 200, 1600);
    
    TCanvas* c = new TCanvas("c", "TIMES");
    c->cd();
    hP1->Draw();
    
    TCanvas* c2 = new TCanvas("c2", "c2");
    c2->cd();
    
}

void Fit_bkg(TString path) {
    gStyle->SetOptFit(1111);
    
    TTree* t = new TTree("t", "Tree");
    t->ReadFile(path, "N_event/D:t_trig:tP1:tP2:tP3");
    
    TH1F* hP1 = new TH1F("hP1", "times in P1", 100, 0., 3500.);
    t->Draw("tP1 >> hP1");

    hP1->SetTitle("Times in P1; time (ticks... FARE CALIBRAZ); Counts");
    hP1->GetXaxis()->SetRange(0.,4000.);
    hP1->SetMaximum(400);
    
    TF1* f_exp = new TF1("f_exp", "[0]*e^(-x/[1])+[2]");
    f_exp->SetParNames("A","tau","b");
    f_exp->SetParameters(300, 2200, 0.5);
    
    hP1->Fit("f_exp", "", "", 200, 1600);
    
    TCanvas* c = new TCanvas("c", "TIMES");
    c->cd();
    hP1->Draw();
    
    TCanvas* c2 = new TCanvas("c2", "c2");
    c2->cd();
    
}

void Calibration(TString path) {
    gStyle->SetOptFit(0011);
    
    TGraphErrors* gr = new TGraphErrors(path, "%lg %*lg %lg %*lg %lg %*lg %lg", ",");
    
    gr->SetTitle("Time calibration (P2); #Deltat oscilloscope (ns); DAQ clock (ticks)");
    gr->SetMarkerStyle(7);
    
    TF1* line = new TF1("line", "[0]*x+[1]");
    line->SetParameters(0.25, -10.24);
    line->SetParNames("m", "q");
    gr->Fit(line);
    
    TLegend* leg = new TLegend(.1, .7, .4, .9);
    leg->AddEntry(gr, "Experimental points");
    leg->AddEntry(line, "Linear fit Y = mX + q");
    
    gr->Draw("AP");
    leg->Draw("SAME");
    
}

void Analysis() {
    
    // TString path_HV("./Data/HV78.csv");
    // Plot_HV(path_HV);
    // TString path_Thr("./Data/Thres78.csv");
    // Plot_Thr(path_Thr);
    
    // TString path_times("./Data/R3_data_2.csv");
    // Fit_bkg(path_times);
    
    TString path_calibration("./Data/Calibration/Calibration.csv");
    Calibration(path_calibration);
    
}
