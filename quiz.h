#pragma once

#include <cmath>

namespace ProjectQuizTest
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Vertex
    {
    public:
        Point Position;
        Vertex(Point p) 
        { 
            Position = p; 
        }
    };

    public ref class Edge
    {
    public:
        Vertex^ StartVertex;
        Vertex^ EndVertex;
        Edge(Vertex^ start, Vertex^ end) 
        { 
            StartVertex = start; 
            EndVertex = end; 
        }
    };

    public ref class quiz : public System::Windows::Forms::Form
    {
    private:
        List<Vertex^>^ vertexList;
        List<Edge^>^ edgeList;
        Vertex^ selectedVertex;

        int globalVertexRadius = 15;
        Color globalVertexColor = Color::SkyBlue;
        Color globalEdgeColor = Color::Black;

        System::Windows::Forms::Panel^ drawingCanvas;
        System::Windows::Forms::Button^ btnResetCanvas;
        System::Windows::Forms::Panel^ settingsPanel;
        System::Windows::Forms::Button^ btnConfirmSettings;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::NumericUpDown^ inputRadius;
        System::Windows::Forms::Button^ btnSelectVertexColor;
        System::Windows::Forms::Button^ btnSelectEdgeColor;
        System::Windows::Forms::Label^ lblRadiusText;

    public:
        quiz(void)
        {
            InitializeComponent();
            vertexList = gcnew List<Vertex^>();
            edgeList = gcnew List<Edge^>();
            selectedVertex = nullptr;
        }

    private:
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->drawingCanvas = (gcnew System::Windows::Forms::Panel());
            this->btnResetCanvas = (gcnew System::Windows::Forms::Button());

            this->drawingCanvas->BackColor = Color::White;
            this->drawingCanvas->BorderStyle = BorderStyle::FixedSingle;
            this->drawingCanvas->Location = Point(20, 20);
            this->drawingCanvas->Size = System::Drawing::Size(740, 400);
            this->drawingCanvas->Anchor = (AnchorStyles)(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
            this->drawingCanvas->Paint += gcnew PaintEventHandler(this, &quiz::OnCanvasPaint);
            this->drawingCanvas->MouseDown += gcnew MouseEventHandler(this, &quiz::OnCanvasMouseDown);

            this->btnResetCanvas->Text = L"Clear Canvas";
            this->btnResetCanvas->Location = Point(20, 440);
            this->btnResetCanvas->Size = System::Drawing::Size(150, 35);
            this->btnResetCanvas->Anchor = (AnchorStyles)(AnchorStyles::Bottom | AnchorStyles::Left);
            this->btnResetCanvas->Click += gcnew EventHandler(this, &quiz::OnResetClick);

            this->settingsPanel = (gcnew System::Windows::Forms::Panel());
            this->settingsPanel->Dock = DockStyle::Fill;
            this->settingsPanel->BackColor = Color::FromArgb(240, 240, 240);

            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblTitle->Text = L"Graph Visualization Settings";
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, FontStyle::Bold));
            this->lblTitle->AutoSize = true;

            this->lblRadiusText = (gcnew System::Windows::Forms::Label());
            this->lblRadiusText->Text = L"Vertex Radius:";
            this->lblRadiusText->AutoSize = true;

            this->inputRadius = (gcnew System::Windows::Forms::NumericUpDown());
            this->inputRadius->Minimum = 5;
            this->inputRadius->Maximum = 50;
            this->inputRadius->Value = 15;

            this->btnSelectVertexColor = (gcnew System::Windows::Forms::Button());
            this->btnSelectVertexColor->Text = L"Vertex Color";
            this->btnSelectVertexColor->BackColor = Color::SkyBlue;
            this->btnSelectVertexColor->Click += gcnew EventHandler(this, &quiz::OnPickVertexColor);

            this->btnSelectEdgeColor = (gcnew System::Windows::Forms::Button());
            this->btnSelectEdgeColor->Text = L"Edge Color";
            this->btnSelectEdgeColor->BackColor = Color::Black;
            this->btnSelectEdgeColor->ForeColor = Color::White;
            this->btnSelectEdgeColor->Click += gcnew EventHandler(this, &quiz::OnPickEdgeColor);

            this->btnConfirmSettings = (gcnew System::Windows::Forms::Button());
            this->btnConfirmSettings->Text = L"START DRAWING";
            this->btnConfirmSettings->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold));
            this->btnConfirmSettings->Size = System::Drawing::Size(200, 50);
            this->btnConfirmSettings->Click += gcnew EventHandler(this, &quiz::OnStartDrawingClick);

            this->settingsPanel->Controls->Add(lblTitle);
            this->settingsPanel->Controls->Add(lblRadiusText);
            this->settingsPanel->Controls->Add(inputRadius);
            this->settingsPanel->Controls->Add(btnSelectVertexColor);
            this->settingsPanel->Controls->Add(btnSelectEdgeColor);
            this->settingsPanel->Controls->Add(btnConfirmSettings);
            this->settingsPanel->Layout += gcnew LayoutEventHandler(this, &quiz::ArrangeSettingsLayout);

            this->ClientSize = System::Drawing::Size(800, 500);
            this->MinimumSize = System::Drawing::Size(500, 450);
            this->Controls->Add(this->settingsPanel);
            this->Controls->Add(this->drawingCanvas);
            this->Controls->Add(this->btnResetCanvas);

            this->Text = L"Graph Designer Pro";
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        void ArrangeSettingsLayout(Object^ sender, LayoutEventArgs^ e)
        {
            int centerX = settingsPanel->Width / 2;
            int centerY = settingsPanel->Height / 2;
            lblTitle->Location = Point(centerX - lblTitle->Width / 2, centerY - 150);
            lblRadiusText->Location = Point(centerX - 90, centerY - 60);
            inputRadius->Location = Point(centerX + 30, centerY - 62);
            btnSelectVertexColor->Size = System::Drawing::Size(160, 35);
            btnSelectVertexColor->Location = Point(centerX - 80, centerY - 10);
            btnSelectEdgeColor->Size = System::Drawing::Size(160, 35);
            btnSelectEdgeColor->Location = Point(centerX - 80, centerY + 35);
            btnConfirmSettings->Location = Point(centerX - 100, centerY + 100);
        }

        void OnPickVertexColor(Object^ sender, EventArgs^ e) 
        {
            ColorDialog^ dialog = gcnew ColorDialog();
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) 
            {
                globalVertexColor = dialog->Color;
                btnSelectVertexColor->BackColor = dialog->Color;
            }
        }

        void OnPickEdgeColor(Object^ sender, EventArgs^ e) 
        {
            ColorDialog^ dialog = gcnew ColorDialog();
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) 
            {
                globalEdgeColor = dialog->Color;
                btnSelectEdgeColor->BackColor = dialog->Color;
            }
        }

        void OnStartDrawingClick(Object^ sender, EventArgs^ e)
        {
            globalVertexRadius = (int)inputRadius->Value;
            this->settingsPanel->Visible = false;
        }

        void OnCanvasMouseDown(Object^ sender, MouseEventArgs^ e)
        {
            Vertex^ targetVertex = nullptr;
            bool isSpaceOccupied = false;
            double safetyMargin = 50.0;

            for (int i = 0; i < vertexList->Count; i++)
            {
                Vertex^ v = vertexList[i];
                double distance = Math::Sqrt(Math::Pow(v->Position.X - e->X, 2) + Math::Pow(v->Position.Y - e->Y, 2));

                if (distance < globalVertexRadius + 5)
                {
                    targetVertex = v;
                    break;
                }
                if (distance < safetyMargin) isSpaceOccupied = true;
            }

            if (e->Button == System::Windows::Forms::MouseButtons::Right)
            {
                if (targetVertex != nullptr)
                {
                    for (int i = edgeList->Count - 1; i >= 0; i--)
                    {
                        if (edgeList[i]->StartVertex == targetVertex || edgeList[i]->EndVertex == targetVertex)
                        {
                            edgeList->RemoveAt(i);
                        }
                    }
                    vertexList->Remove(targetVertex);
                    if (selectedVertex == targetVertex) selectedVertex = nullptr;
                }
            }
            else if (e->Button == System::Windows::Forms::MouseButtons::Left)
            {
                if (targetVertex == nullptr)
                {
                    if (!isSpaceOccupied)
                    {
                        vertexList->Add(gcnew Vertex(e->Location));
                        selectedVertex = nullptr;
                    }
                }
                else
                {
                    if (selectedVertex == nullptr) selectedVertex = targetVertex;
                    else if (selectedVertex != targetVertex)
                    {
                        edgeList->Add(gcnew Edge(selectedVertex, targetVertex));
                        selectedVertex = nullptr;
                    }
                    else selectedVertex = nullptr;
                }
            }
            drawingCanvas->Invalidate();
        }

        void OnCanvasPaint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ graphics = e->Graphics;
            graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

            Pen^ linePen = gcnew Pen(globalEdgeColor, 2);
            for (int i = 0; i < edgeList->Count; i++)
            {
                graphics->DrawLine(linePen, edgeList[i]->StartVertex->Position, edgeList[i]->EndVertex->Position);
            }

            for (int i = 0; i < vertexList->Count; i++)
            {
                Vertex^ currentVertex = vertexList[i];
                Brush^ fillBrush = (currentVertex == selectedVertex) ? Brushes::Red : gcnew SolidBrush(globalVertexColor);

                int diameter = globalVertexRadius * 2;
                Rectangle drawRect(currentVertex->Position.X - globalVertexRadius, currentVertex->Position.Y - globalVertexRadius, diameter, diameter);

                graphics->FillEllipse(fillBrush, drawRect);
                graphics->DrawEllipse(Pens::Black, drawRect);

                String^ label = (i + 1).ToString();
                System::Drawing::Font^ textFont = gcnew System::Drawing::Font("Segoe UI", (float)(globalVertexRadius * 0.7 + 3), FontStyle::Bold);
                SizeF textSize = graphics->MeasureString(label, textFont);
                graphics->DrawString(label, textFont, Brushes::Black, currentVertex->Position.X - textSize.Width / 2, currentVertex->Position.Y - textSize.Height / 2);
            }
        }

        void OnResetClick(Object^ sender, EventArgs^ e)
        {
            vertexList->Clear();
            edgeList->Clear();
            selectedVertex = nullptr;
            drawingCanvas->Invalidate();
        }

    private:
        System::ComponentModel::IContainer^ components;
    };
}
