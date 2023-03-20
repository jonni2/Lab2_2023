// Root Program to perform data analysis

// function to plot a CSV file
void Plot(TString path) {
    
    TGraph* g1 = new TGraph(path, "%lg %*lg %*lg %lg", ",");
    
    g1->SetTitle("High Voltage scan, PMT 7, 8, using 9, 10 as REFs; PMTs Voltage (V); Counts");
    g1->SetMarkerStyle(6);
    g1->SetMarkerColor(kBlue);
    g1->SetLineColor(kBlue);
    
    TGraph* g2 = new TGraph(path, "%lg %*lg %*lg %*lg %lg", ",");
    g2->SetMarkerStyle(6);
    g2->SetMarkerSize(2);
    g2->SetMarkerColor(kRed);
    g2->SetLineColor(kRed);
    
    TLegend* leg = new TLegend(.1, .7, .4, .9);
    leg->AddEntry(g1, "PMT 7 coinc. with 9, 10");
    leg->AddEntry(g2, "PMT 8 coinc. with 9, 10");
    
    TCanvas* c = new TCanvas("c", "HV scan");
    c->cd();
    g1->Draw("APL");
    g2->Draw("PL,SAME");
    leg->Draw("SAME");
    
}



void Analysis() {
    
    TString path("./HV78.csv");
    Plot(path);
    
}
