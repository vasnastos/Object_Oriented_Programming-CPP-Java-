#include <wx/wx.h>
#include <wx/ListCtrl.h>
#include "Surfer.hpp"
#include <fstream>
#include <string>
#define RAN 90
#define SAVE 112
#define RNK 111
#define EXIT 113


class app:public wxApp
{
    public:
       bool OnInit()wxOVERRIDE;
};

class window:public wxFrame
{
    private:
       int vs;
       int pgs;
       std::string res;
       wxBoxSizer *bx;
       wxTextCtrl *visitors,*pages,*dp,*results;
       wxListCtrl *ranking;
       void Clearlist()
       {
           this->ranking->ClearAll();
           wxListItem col1;
           col1.SetWidth(110);
           col1.SetId(0);
           col1.SetText(_("RANK"));
           wxListItem col2;
           col2.SetWidth(110);
           col2.SetId(1);
           col2.SetText(_("WEB PAGE"));
           wxListItem col3;
           col3.SetId(2);
           col3.SetWidth(110);
           col3.SetText(_("GRADE"));
           this->ranking->InsertColumn(0,col1);
           this->ranking->InsertColumn(1,col2);
           this->ranking->InsertColumn(2,col3);
       }
       void make_menu()
       {
           //Δημιουργία μενού και σύνδεση με ενέργεια.
           wxMenuBar *bar=new wxMenuBar();
           wxMenu *m=new wxMenu();
           m->Append(SAVE,"SAVE SURF");
           m->Append(RNK,"SAVE RANK");
           m->Append(EXIT,"EXIT");
           Connect(SAVE,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(window::Save));
           Connect(RNK,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(window::SaveTable));
           Connect(EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(window::Exit));
           bar->Append(m,"OPTIONS");
           this->SetMenuBar(bar);
       }
       void panel1()
       {
           wxPanel *panel=new wxPanel(this,wxID_ANY);
           wxGridSizer *siz=new wxGridSizer(0,2,5,5);
           wxStaticText *st=new wxStaticText(panel,wxTEXT_ALINGMENT_CENTER,"VISITORS",wxDefaultPosition);
           st->SetForegroundColour(wxColor("#54394a"));
           st->SetBackgroundColour(wxColor("#abe6a5"));
           this->visitors=new wxTextCtrl(panel,wxID_ANY,"3",wxDefaultPosition,wxSize(100,20));
           siz->Add(st,wxALIGN_CENTER_HORIZONTAL);
           siz->Add(this->visitors);
           panel->SetSizer(siz);
           this->bx->Add(panel);
       }
       void Damping_panel()
       {
           wxPanel *panel=new wxPanel(this,wxID_ANY);
           wxGridSizer *gs=new wxGridSizer(0,2,5,5);
           wxStaticText *st=new wxStaticText(panel,wxID_ANY,"Damping Factor",wxDefaultPosition,wxSize(100,20));
           st->SetForegroundColour(wxColor("#54394a"));
           st->SetBackgroundColour(wxColor("#abe6a5"));
           this->dp=new wxTextCtrl(panel,wxID_ANY,"0.85",wxDefaultPosition,wxSize(100,20));
           gs->Add(st);
           gs->Add(this->dp);
           panel->SetSizer(gs);
           this->bx->Add(panel);
       }
       void panel2()
       {
           wxPanel *panel=new wxPanel(this,wxID_ANY);
           wxGridSizer *siz=new wxGridSizer(0,2,5,5);
           wxStaticText *st=new wxStaticText(panel,wxTEXT_ALIGNMENT_CENTER,"PAGES",wxDefaultPosition,wxSize(100,20));
           st->SetForegroundColour(wxColor("#54394a"));
           st->SetBackgroundColour(wxColor("#abe6a5"));
           this->pages=new wxTextCtrl(panel,wxID_ANY,"10",wxDefaultPosition,wxSize(100,20));
           siz->Add(st);
           siz->Add(this->pages);
           panel->SetSizer(siz);
           this->bx->Add(panel); 
       }
       void buttonpanel()
       {
           wxPanel *panel=new wxPanel(this,wxID_ANY);
           wxGridSizer *siz=new wxGridSizer(0,2,5,5);
           wxButton *b1=new wxButton(panel,wxID_ANY,"SURF",wxDefaultPosition,wxSize(60,20));
           wxButton *b2=new wxButton(panel,wxID_ANY,"CLEAR",wxDefaultPosition,wxSize(60,20));
           b1->Bind(wxEVT_BUTTON,&window::surf,this);
           b2->Bind(wxEVT_BUTTON,&window::clear,this);
           siz->Add(b1);
           siz->Add(b2);
           panel->SetSizer(siz);
           this->bx->Add(panel);
       }
       void ranking_panel()
       {
           this->ranking=new wxListCtrl(this,wxID_ANY,wxDefaultPosition,wxSize(330,250),wxLC_REPORT);
           wxListItem col1;
           col1.SetWidth(110);
           col1.SetId(0);
           col1.SetText(_("RANK"));
           wxListItem col2;
           col2.SetWidth(110);
           col2.SetId(1);
           col2.SetText(_("WEB PAGE"));
           wxListItem col3;
           col3.SetId(2);
           col3.SetWidth(110);
           col3.SetText(_("GRADE"));
           this->ranking->InsertColumn(0,col1);
           this->ranking->InsertColumn(1,col2);
           this->ranking->InsertColumn(2,col3);
           
           //Εισαγωγή αντικειμένου στην λίστα
           wxListItem it;
           it.SetId(RAN);
           it.SetText("Here we are inserted the ranking results of Random Surfing");
           this->ranking->InsertItem(it);

           //Τροποποίηση με βάση τις στήλες
           this->ranking->SetItem(0,0,"Rank Column");
           this->ranking->SetItem(0,1,"Vertex Column");
           this->ranking->SetItem(0,2,"Grade Column");

           this->bx->Add(this->ranking);
       }
       void resultspanel()
       {
           this->results=new wxTextCtrl(this,wxID_ANY,"",wxDefaultPosition,wxSize(330,280),wxTE_MULTILINE);
           this->bx->Add(this->results);
       }
    public:
       window():wxFrame(NULL,wxID_ANY,"Random Surfer")
       {
           this->SetSize(350,600);
           this->bx=new wxBoxSizer(wxVERTICAL);
           wxStaticText *st=new wxStaticText(this,wxALIGN_CENTRE_HORIZONTAL,"RANDOM SURFER ALGORITHM");
           st->SetForegroundColour(wxColor("#0d0e0f"));
           st->SetBackgroundColour(wxColor("#e0e319"));
           this->bx->Add(st);
           this->make_menu();
           this->panel1();
           this->Damping_panel();
           this->panel2();
           this->buttonpanel();
           this->resultspanel();
           this->ranking_panel();
           this->SetSizer(this->bx);
           Center();
       }
       ~window()
       {
           exit(EXIT_SUCCESS);
       }
       void surf(wxCommandEvent &ev)
       {
           //Γεγονός που θα εκτελείται όταν πατήται το κουμπί.
           //Εκχωρώ την τιμή από το πεδίο εισόδου σε ένα αλφαριθμητικό.
          std::string vis=std::string(this->visitors->GetValue());
          std::string pgs=std::string(this->pages->GetValue());
          std::string dampingfactor=std::string(this->dp->GetValue());
          if(vis.empty() || pgs.empty() || dampingfactor.empty())
          {
              wxMessageBox("Fill all the blanks");
              return;
          }
          int visitor=std::stoi(vis);
          int page=std::stoi(pgs);
          double dampfactor=std::stod(dampingfactor);
          this->vs=visitor;
          this->pgs=page;
          if(visitor==0  || page==0 || dampfactor<0.0)
          {
              wxMessageBox("0 number detected!!Surfer algorithm not executed");
              return;
          }
          Surfer s(page);
          this->res=s.Random_Surfing(visitor,dampfactor);
          this->results->SetValue(res);
       }
       void clear(wxCommandEvent &ev)
       {
          this->visitors->SetValue("");
          this->pages->SetValue("");
          this->dp->SetValue("");
          this->results->SetValue("");
          this->Clearlist();
       }
       void Save(wxCommandEvent &ev)
       {
           if(Surfer::countcalls==0) {return;}
          std::ofstream os;
          std::string date=__DATE__;
          std::string time=__TIME__;
          std::string filename="Surfing_"+date+"_time.out";
          os.open(filename);
          os<<"Random Surfing Saved information"<<std::endl;
          os<<"File Created at:"<<__DATE__<<"-"<<__TIME__<<std::endl;
          os<<"Visitors:"<<this->vs<<std::endl;
          os<<"Pages:"<<this->pgs<<std::endl;
          os<<"Iterations made:"<<Surfer::countcalls<<std::endl;
          os<<"Surfs Made"<<std::endl;
          os<<"---------------------------------------------------------------"<<std::endl;
          os<<this->res<<std::endl;
          os.close();
       }
       void SaveTable(wxCommandEvent &ev)
       {
           if(matrix::ranking.empty()) return;
          std::string time=__TIME__;
          std::string date=__DATE__;
          std::ofstream os;
          os.open("Ranking_"+date+".out");
          os<<"File Saving Ranking from of the Web Pages"<<std::endl;
          os<<"File Created at:"<<date<<"-"<<time<<std::endl;
          os<<"Pages:"<<this->pgs<<std::endl;
          os<<"Iterations:"<<Surfer::countcalls<<std::endl;
          os<<"--------------------------------------------------------------------------"<<std::endl;
          os<<"\tRANK\tPAGE\tGRADE"<<std::endl;
          int counter=1;
          for(auto &x:matrix::ranking)
          {
              os<<"\t "<<counter<<"   \t  "<<x.vertex<<"   \t "<<x.rank<<std::endl;
              counter++;
          }
          os.close();
          wxMessageBox("Ranking info have been saved in Ranking_"+date+"-"+time+".out file");
       }
       void Exit(wxCommandEvent &ev)
       {
           exit(EXIT_SUCCESS);
       }
};

bool app::OnInit()
{
    window *w=new window();
    w->Show();
    return true;
}

wxIMPLEMENT_APP(app);