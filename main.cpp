#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE()
};

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(wxT("Minimal wxWidgets App"));
    frame->Show(true);

    return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
END_EVENT_TABLE()

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"),
    wxVERSION_STRING);
    wxMessageBox(msg, wxT("About Minimal"),
    wxOK | wxICON_INFORMATION, this);
}
void MyFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

MyFrame::MyFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
    wxMenu *fileMenu = new wxMenu;

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
    wxT("Show about dialog"));
    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
    wxT("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}
// using json = nlohmann::json;
//
// size_t WriteCallback(void* contents, const size_t size, const size_t nmemb, std::string* output) {
//     const size_t totalSize = size * nmemb;
//
//     output->append(static_cast<char *>(contents), totalSize);
//     return totalSize;
// }
//
// int main() {
//     std::string readBuffer;
//
//     const std::string apiKey = "9ff0c523-4d02-4bd0-9a03-91c44aa2bcf2";
//     const std::string url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?id=1&convert=UAH";
//     const std::string byc_url = "https://pro-api.coinmarketcap.com/v1/blockchain/statistics/latest";
//
//     curl_global_init(CURL_GLOBAL_DEFAULT);
//     if(CURL *curl = curl_easy_init()) {
//         curl_slist* headers = nullptr;
//         headers = curl_slist_append(headers, ("X-CMC_PRO_API_KEY: " + apiKey).c_str());
//         headers = curl_slist_append(headers, "Accept: application/json");
//
//         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//
//         if(const CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
//             std::cerr << "Ошибка curl: " << curl_easy_strerror(res) << std::endl;
//         } else {
//             try {
//                 json j = json::parse(readBuffer);
//                 auto quotes = j["data"]["1"]["quote"];
//
//                 std::cout << "Курс Bitcoin (BTC):\n";
//                 std::cout << "UAH: " << quotes["UAH"]["price"] << "\n";
//             } catch (std::exception& e) {
//                 std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
//             }
//         }
//
//         curl_slist_free_all(headers);
//         curl_easy_cleanup(curl);
//     }
//     curl_global_cleanup();
//
//     return 0;
// }
