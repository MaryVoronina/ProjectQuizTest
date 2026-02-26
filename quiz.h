#pragma once

namespace ProjectQuizTest
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class quiz : public System::Windows::Forms::Form
    {
    private:
        array<int>^ mas_data;
        int arraySize, i, j;
        bool isSorted, swapped, isSpeedSelected;
        int MAX_VALUE;

        System::Windows::Forms::Panel^ drawPanel;
        System::Windows::Forms::Button^ button_next;
        System::Windows::Forms::Button^ button_auto;
        System::Windows::Forms::Timer^ sortTimer;
        System::Windows::Forms::MenuStrip^ menuStrip1;

        System::Windows::Forms::ToolStripMenuItem^ menuFile, ^ openItem, ^ saveItem, ^ randomItem;
        System::Windows::Forms::ToolStripMenuItem^ menuSpeed, ^ slowItem, ^ medItem, ^ fastItem;

        System::Windows::Forms::Panel^ startPanel;
        System::Windows::Forms::Button^ btnStartProject;
        System::Windows::Forms::Label^ lblWelcome;

    public:
        quiz(void)
        {
            InitializeComponent();
            MAX_VALUE = 100;
            mas_data = nullptr;
            isSorted = true;
            swapped = false;
            isSpeedSelected = false;
        }

    private:
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->sortTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());

            this->menuFile = (gcnew System::Windows::Forms::ToolStripMenuItem(L"File"));
            this->openItem = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Open"));
            this->saveItem = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Save"));
            this->randomItem = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Randomize"));

            this->menuSpeed = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Speed"));
            this->slowItem = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Slow (600ms)"));
            this->medItem = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Medium (300ms)"));
            this->fastItem = (gcnew System::Windows::Forms::ToolStripMenuItem(L"Fast (50ms)"));

            this->drawPanel = (gcnew System::Windows::Forms::Panel());
            this->button_next = (gcnew System::Windows::Forms::Button());
            this->button_auto = (gcnew System::Windows::Forms::Button());

            this->sortTimer->Interval = 100;
            this->sortTimer->Tick += gcnew System::EventHandler(this, &quiz::OnTimerTick);

            this->menuStrip1->Items->AddRange(gcnew array<ToolStripItem^>{menuFile, menuSpeed});
            this->menuFile->DropDownItems->AddRange(gcnew array<ToolStripItem^>{openItem, saveItem, randomItem});
            this->menuSpeed->DropDownItems->AddRange(gcnew array<ToolStripItem^>{slowItem, medItem, fastItem});
            this->menuStrip1->Visible = false;

            this->openItem->Click += gcnew EventHandler(this, &quiz::open_file);
            this->saveItem->Click += gcnew EventHandler(this, &quiz::save_file);
            this->randomItem->Click += gcnew EventHandler(this, &quiz::button_reset_Click);

            this->slowItem->Click += gcnew EventHandler(this, &quiz::SetSpeedSlow);
            this->medItem->Click += gcnew EventHandler(this, &quiz::SetSpeedMed);
            this->fastItem->Click += gcnew EventHandler(this, &quiz::SetSpeedFast);

            this->drawPanel->BackColor = Color::White;
            this->drawPanel->BorderStyle = BorderStyle::FixedSingle;
            this->drawPanel->Location = Point(20, 40);
            this->drawPanel->Size = System::Drawing::Size(740, 400);
            this->drawPanel->Anchor = (AnchorStyles)(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
            this->drawPanel->Paint += gcnew PaintEventHandler(this, &quiz::drawPanel_Paint);

            this->button_next->Text = L"Next Step";
            this->button_next->Location = Point(20, 460);
            this->button_next->Size = System::Drawing::Size(180, 40);
            this->button_next->Anchor = (AnchorStyles)(AnchorStyles::Bottom | AnchorStyles::Left);
            this->button_next->Click += gcnew EventHandler(this, &quiz::button_next_Click);

            this->button_auto->Text = L"Auto Sort";
            this->button_auto->Location = Point(210, 460);
            this->button_auto->Size = System::Drawing::Size(180, 40);
            this->button_auto->Anchor = (AnchorStyles)(AnchorStyles::Bottom | AnchorStyles::Left);
            this->button_auto->Click += gcnew EventHandler(this, &quiz::button_auto_Click);

            this->startPanel = (gcnew System::Windows::Forms::Panel());
            this->startPanel->Dock = DockStyle::Fill;
            this->startPanel->BackColor = Color::White;

            this->lblWelcome = (gcnew System::Windows::Forms::Label());
            this->lblWelcome->Text = L"Bubble Sort Visualizer";
            this->lblWelcome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, FontStyle::Bold));
            this->lblWelcome->AutoSize = true;

            this->btnStartProject = (gcnew System::Windows::Forms::Button());
            this->btnStartProject->Text = L"START";
            this->btnStartProject->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, FontStyle::Bold));
            this->btnStartProject->Size = System::Drawing::Size(200, 60);
            this->btnStartProject->Click += gcnew EventHandler(this, &quiz::OnStartBtnClick);

            this->startPanel->Controls->Add(lblWelcome);
            this->startPanel->Controls->Add(btnStartProject);
            this->startPanel->Layout += gcnew LayoutEventHandler(this, &quiz::CenterStartElements);

            this->ClientSize = System::Drawing::Size(800, 520);
            this->Controls->Add(this->startPanel);
            this->Controls->Add(this->drawPanel);
            this->Controls->Add(this->button_next);
            this->Controls->Add(this->button_auto);
            this->Controls->Add(this->menuStrip1);
            this->MainMenuStrip = this->menuStrip1;
            this->Text = L"Sorting Visualizer";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Resize += gcnew EventHandler(this, &quiz::Form_Resize);
        }

        void SetSpeedSlow(Object^ sender, EventArgs^ e) 
        { 
            this->sortTimer->Interval = 600; 
            isSpeedSelected = true; 
        }
        void SetSpeedMed(Object^ sender, EventArgs^ e) 
        { 
            this->sortTimer->Interval = 300; 
            isSpeedSelected = true; 
        }
        void SetSpeedFast(Object^ sender, EventArgs^ e) 
        { 
            this->sortTimer->Interval = 50; 
            isSpeedSelected = true;
        }

        void OnTimerTick(Object^ sender, EventArgs^ e)
        {
            if (mas_data != nullptr && !isSorted)
            {
                perform_step();
                drawPanel->Invalidate();
            }
            else sortTimer->Stop(); 
        }

        void CenterStartElements(Object^ sender, LayoutEventArgs^ e)
        {
            lblWelcome->Location = Point((startPanel->Width - lblWelcome->Width) / 2, (startPanel->Height / 2) - 80);
            btnStartProject->Location = Point((startPanel->Width - btnStartProject->Width) / 2, (startPanel->Height / 2) + 20);
        }

        void OnStartBtnClick(Object^ sender, EventArgs^ e)
        {
            this->startPanel->Visible = false;
            this->menuStrip1->Visible = true;
            mas_data = nullptr;
            arraySize = 0;
            isSorted = true;
            isSpeedSelected = false;
            this->drawPanel->Invalidate();
        }

        void perform_step()
        {
            if (i < arraySize - 1)
            {
                if (j < arraySize - i - 1)
                {
                    if (mas_data[j] > mas_data[j + 1])
                    {
                        int tmp = mas_data[j];
                        mas_data[j] = mas_data[j + 1];
                        mas_data[j + 1] = tmp;
                        swapped = true;
                    }
                    j++;
                }
                else
                {
                    if (!swapped) 
                    { 
                        finish_sorting(); 
                        return; 
                    }
                    j = 0; 
                    i++;
                    swapped = false;
                }
            }
            else finish_sorting();
        }

        void finish_sorting()
        {
            sortTimer->Stop();
            isSorted = true;
            i = arraySize;
            j = -1;
            this->drawPanel->Invalidate();
            MessageBox::Show("Sorting complete!", "Done");
        }

        System::Void button_next_Click(Object^ sender, EventArgs^ e)
        {
            sortTimer->Stop();
            if (mas_data == nullptr) 
            {
                MessageBox::Show("Select or generate an array!", "Error");
                return;
            }
            if (!isSorted)
            {
                perform_step();
                drawPanel->Invalidate();
            }
        }

        System::Void button_auto_Click(Object^ sender, EventArgs^ e)
        {
            if (mas_data == nullptr) {
                MessageBox::Show("Please select an array!", "Warning");
                return;
            }
            if (!isSpeedSelected) {
                MessageBox::Show("Please choose a speed!", "Warning");
                return;
            }

            if (!isSorted) sortTimer->Start(); 
        }

        System::Void button_reset_Click(Object^ sender, EventArgs^ e)
        {
            sortTimer->Stop();
            Random^ rnd = gcnew Random();
            arraySize = rnd->Next(5, 15);
            mas_data = gcnew array<int>(arraySize);
            for (int k = 0; k < arraySize; k++) 
            { 
                mas_data[k] = rnd->Next(5, MAX_VALUE); 
            }
            i = 0; 
            j = 0; 
            isSorted = false; 
            swapped = false;
            drawPanel->Invalidate();
        }

        System::Void drawPanel_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            if (mas_data == nullptr) return;
            float barSpacing = (float)drawPanel->Width / arraySize;
            float barWidth = barSpacing * 0.75f;
            int maxValue = 1;
            for (int k = 0; k < arraySize; k++) { if (mas_data[k] > maxValue) maxValue = mas_data[k]; }

            for (int k = 0; k < arraySize; k++)
            {
                int bh = (int)((mas_data[k] / (float)maxValue) * (drawPanel->Height - 75));
                float x = k * barSpacing + (barSpacing - barWidth) / 2;
                float y = drawPanel->Height - bh - 25;

                Brush^ barBrush;
                if (isSorted || k >= arraySize - i) 
                { 
                    barBrush = Brushes::LightGreen; 
                }
                else if (k == j || k == j + 1) 
                { 
                    barBrush = Brushes::LightPink; 
                }
                else 
                { 
                    barBrush = Brushes::SkyBlue; 
                }

                g->FillRectangle(barBrush, x, y, barWidth, (float)bh);
                g->DrawRectangle(Pens::Black, x, y, barWidth, (float)bh);
                g->DrawString(mas_data[k].ToString(), gcnew System::Drawing::Font("Arial", 9, FontStyle::Bold), Brushes::Black, x, y - 20);
            }
        }

        System::Void open_file(Object^ sender, EventArgs^ e)
        {
            sortTimer->Stop();
            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                String^ content = File::ReadAllText(ofd->FileName);
                array<String^>^ num = content->Split(gcnew array<Char>{' ', '\n', '\r', '\t', ','}, StringSplitOptions::RemoveEmptyEntries);
                if (num->Length > 0)
                {
                    arraySize = num->Length;
                    mas_data = gcnew array<int>(arraySize);
                    for (int k = 0; k < arraySize; k++) 
                    { 
                        Int32::TryParse(num[k], mas_data[k]); 
                    }
                    i = 0; 
                    j = 0; 
                    isSorted = false; 
                    swapped = false;
                    drawPanel->Invalidate();
                }
            }
        }

        System::Void save_file(Object^ sender, EventArgs^ e)
        {
            if (mas_data == nullptr) return;
            SaveFileDialog^ sfd = gcnew SaveFileDialog();
            if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                String^ res = "";
                for (int k = 0; k < arraySize; k++)
                {
                    res += mas_data[k].ToString() + " ";
                }
                    
                File::WriteAllText(sfd->FileName, res);
            }
        }

        System::Void Form_Resize(Object^ sender, EventArgs^ e)
        {
            if (startPanel->Visible) 
                CenterStartElements(nullptr, nullptr);
            drawPanel->Invalidate();
        }

    private:
        System::ComponentModel::IContainer^ components;
    };
}
