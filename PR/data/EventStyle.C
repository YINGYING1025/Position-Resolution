void EventStyle()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed May 13 07:27:55 2020) by ROOT version 6.16/00
   TCanvas *c1 = new TCanvas("c1", "c1",10,45,700,500);
   c1->Range(-0.6250001,-4145.663,5.625,37310.96);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *h1__1 = new TH1F("h1__1","Event style",5,0,5);
   h1__1->SetBinContent(1,31586);
   h1__1->SetBinContent(2,10812);
   h1__1->SetBinContent(3,12668);
   h1__1->SetBinContent(4,5385);
   h1__1->SetEntries(1064);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("h1");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 1064   ");
   ptstats_LaTex = ptstats->AddText("Mean  =      0");
   ptstats_LaTex = ptstats->AddText("Std Dev   =      0");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h1__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1__1);
   h1__1->SetLineColor(4);
   h1__1->SetLineWidth(4);
   h1__1->GetXaxis()->SetBinLabel(1,"All Event");
   h1__1->GetXaxis()->SetBinLabel(2,"Noise Event");
   h1__1->GetXaxis()->SetBinLabel(3,"Threshold Event");
   h1__1->GetXaxis()->SetBinLabel(4,"ThreeSignal Event");
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetLabelSize(0.035);
   h1__1->GetXaxis()->SetTitleSize(0.035);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetLabelSize(0.035);
   h1__1->GetYaxis()->SetTitleSize(0.035);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetLabelSize(0.035);
   h1__1->GetZaxis()->SetTitleSize(0.035);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("");
   TLatex *   tex = new TLatex(0.5,31585.2,"31586");
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(1.5,10811.2,"10812");
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.5,12667.2,"12668");
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(3.5,5384.2,"5385");
   tex->SetLineWidth(2);
   tex->Draw();
   
   TPaveText *pt = new TPaveText(0.3997421,0.9368947,0.6002579,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Event style");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
