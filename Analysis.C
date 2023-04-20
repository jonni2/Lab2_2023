// Root Program to perform data analysis

// function to plot a CSV file
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

void Plot_times(TString path) {
    gStyle->SetOptFit(1111);
    
    TTree* t = new TTree("t", "Tree");
    t->ReadFile(path, "N_event/D:t_trig:tP1:tP2:tP3");
    
    TH1F* hP1 = new TH1F("hP1", "times in P1", 100, 0., 3500.);
    t->Draw("tP3 >> hP1");

    hP1->SetTitle("Times in P1; time (ns); Counts");
    hP1->GetXaxis()->SetRange(0.,4000.);
    hP1->SetMaximum(400);
    
    TF1* f_exp = new TF1("f_exp", "[0]*e^(-x/[1])+[2]");
    f_exp->SetParNames("A","tau","b");
    f_exp->SetParameters(300, 2200, 0.5);
    
    hP1->Fit("f_exp", "", "", 200, 1600);
    
    TCanvas* c = new TCanvas("c", "TIMES");
    c->cd();
    hP1->Draw();
    
}


void Analysis() {
    
    // TString path_HV("./HV78.csv");
    // Plot_HV(path_HV);
    // TString path_Thr("./Thres78.csv");
    // Plot_Thr(path_Thr);
    
    TString path_times("../Calibration/R3_data_2.csv");
    Plot_times(path_times);
    
}
