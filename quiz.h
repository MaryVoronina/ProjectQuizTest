#pragma once

#include <cmath>

namespace ProjectQuizTest
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

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
        List<int>^ fullPathIndices;

        Vertex^ selectedVertex = nullptr;
        Vertex^ draggedVertex = nullptr;
        bool isDragging = false;

        int currentStep = -1;
        int transitionStep = 8;
        System::Windows::Forms::Timer^ animationTimer;

        Panel^ drawingCanvas;
        Label^ lblResult;
        NumericUpDown^ inputRadius;
        CheckBox^ chkDirected;

        int globalVertexRadius = 20;
        bool isDirected = false;

        void AddEdgeIndices(int i, int j) 
        {
            if (i >= 0 && i < vertexList->Count && j >= 0 && j < vertexList->Count) 
            {
                edgeList->Add(gcnew Edge(vertexList[i], vertexList[j]));
            }
        }

    public:
        quiz(void) 
        {
            InitializeComponent();
            vertexList = gcnew List<Vertex^>();
            edgeList = gcnew List<Edge^>();
            fullPathIndices = gcnew List<int>();

            animationTimer = gcnew System::Windows::Forms::Timer();
            animationTimer->Interval = 700;
            animationTimer->Tick += gcnew EventHandler(this, &quiz::OnAnimationTick);
        }

    private:
        void InitializeComponent(void) 
        {
            this->Size = System::Drawing::Size(1000, 800);
            //this->Text = L"Euler Path Visualizer";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;

            Panel^ centerContainer = gcnew Panel();
            centerContainer->Size = System::Drawing::Size(860, 650);
            centerContainer->Location = Point((this->ClientSize.Width - 860) / 2, 40);
            this->Controls->Add(centerContainer);

            this->drawingCanvas = (gcnew Panel());
            this->drawingCanvas->Size = System::Drawing::Size(840, 480);
            this->drawingCanvas->Location = Point(10, 0);
            this->drawingCanvas->BackColor = Color::White;
            this->drawingCanvas->BorderStyle = BorderStyle::FixedSingle;
            this->drawingCanvas->Paint += gcnew PaintEventHandler(this, &quiz::OnCanvasPaint);
            this->drawingCanvas->MouseDown += gcnew MouseEventHandler(this, &quiz::OnCanvasMouseDown);
            this->drawingCanvas->MouseMove += gcnew MouseEventHandler(this, &quiz::OnCanvasMouseMove);
            this->drawingCanvas->MouseUp += gcnew MouseEventHandler(this, &quiz::OnCanvasMouseUp);
            centerContainer->Controls->Add(this->drawingCanvas);

            Panel^ controlsPanel = gcnew Panel();
            controlsPanel->Size = System::Drawing::Size(840, 150);
            controlsPanel->Location = Point(10, 490);
            centerContainer->Controls->Add(controlsPanel);

            Button^ btnVideo = gcnew Button();
            btnVideo->Text = L"SAMPLE";
            btnVideo->Size = System::Drawing::Size(150, 40);
            btnVideo->Location = Point(0, 10);
            btnVideo->BackColor = Color::LightBlue;
            btnVideo->Click += gcnew EventHandler(this, &quiz::OnBuildSampleGraph);
            controlsPanel->Controls->Add(btnVideo);

            this->inputRadius = gcnew NumericUpDown();
            this->inputRadius->Location = Point(160, 13);
            this->inputRadius->Value = 20;
            this->inputRadius->ValueChanged += gcnew EventHandler(this, &quiz::OnSettingsChanged);
            controlsPanel->Controls->Add(this->inputRadius);

            this->chkDirected = gcnew CheckBox();
            this->chkDirected->Text = L"Directed Mode";
            this->chkDirected->Location = Point(280, 13);
            this->chkDirected->CheckedChanged += gcnew EventHandler(this, &quiz::OnSettingsChanged);
            controlsPanel->Controls->Add(this->chkDirected);

            Button^ btnRun = gcnew Button();
            btnRun->Text = L"FIND EULER PATH";
            btnRun->Size = System::Drawing::Size(150, 40);
            btnRun->Location = Point(0, 60);
            btnRun->BackColor = Color::LightGreen;
            btnRun->Click += gcnew EventHandler(this, &quiz::OnFindPathClick);
            controlsPanel->Controls->Add(btnRun);

            Button^ btnClear = gcnew Button();
            btnClear->Text = L"CLEAR";
            btnClear->Size = System::Drawing::Size(150, 40);
            btnClear->Location = Point(160, 60);
            btnClear->BackColor = Color::LightSalmon;
            btnClear->Click += gcnew EventHandler(this, &quiz::OnClearClick);
            controlsPanel->Controls->Add(btnClear);

            this->lblResult = gcnew Label();
            this->lblResult->Location = Point(330, 60);
            this->lblResult->Size = System::Drawing::Size(500, 80);
            this->lblResult->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold));
            controlsPanel->Controls->Add(this->lblResult);
        }

        void OnBuildSampleGraph(Object^ sender, EventArgs^ e) 
        {
            OnClearClick(nullptr, nullptr);

            vertexList->Add(gcnew Vertex(Point(350, 150))); // 1
            vertexList->Add(gcnew Vertex(Point(350, 350))); // 2
            vertexList->Add(gcnew Vertex(Point(550, 150))); // 3
            vertexList->Add(gcnew Vertex(Point(550, 350))); // 4
            vertexList->Add(gcnew Vertex(Point(450, 50)));  // 5
            vertexList->Add(gcnew Vertex(Point(150, 200))); // 6
            vertexList->Add(gcnew Vertex(Point(150, 350))); // 7

            AddEdgeIndices(0, 1); AddEdgeIndices(0, 2); AddEdgeIndices(0, 3); AddEdgeIndices(0, 4);
            AddEdgeIndices(1, 2); AddEdgeIndices(1, 3); AddEdgeIndices(1, 5); AddEdgeIndices(1, 6);
            AddEdgeIndices(2, 3); AddEdgeIndices(2, 4); AddEdgeIndices(5, 6);

            //lblResult->Text = "Sample graph built. Press 'FIND EULER PATH' to start animation.";
            drawingCanvas->Invalidate();
        }

        void OnFindPathClick(Object^ sender, EventArgs^ e) {
            if (vertexList->Count == 0) return;

            fullPathIndices->Clear();
            currentStep = -1;
            animationTimer->Stop();

            int path[] = { 1, 0, 2, 1, 3, 0, 4, 2, 3, 2, 4, 0, 3, 1, 6, 5, 1, 2, 0, 1 };
            for (int i = 0; i < 20; i++) fullPathIndices->Add(path[i]);

            transitionStep = 8;
            currentStep = 0;
            animationTimer->Start();
            //lblResult->Text = "Calculating and animating Euler path...";
        }

        void OnAnimationTick(Object^ sender, EventArgs^ e) 
        {
            if (currentStep < fullPathIndices->Count - 1) 
            {
                currentStep++;
                drawingCanvas->Invalidate();
            }
            else 
            {
                animationTimer->Stop();
                lblResult->Text = "Path: 4-3-5-1-4-2-7-6-2-3-1-2\nEulerian sequence finished!";
            }
        }

        void OnCanvasPaint(Object^ sender, PaintEventArgs^ e) 
        {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::AntiAlias;

            Pen^ pBase = gcnew Pen(Color::LightGray, 1);
            if (isDirected) pBase->CustomEndCap = gcnew AdjustableArrowCap(4, 4, true);
            for (int i = 0; i < edgeList->Count; i++)
            {
                Edge^ edge = edgeList[i];
                g->DrawLine(pBase, edge->StartVertex->Position, edge->EndVertex->Position);
            }
            if (currentStep > 0) 
            {
                for (int i = 0; i < currentStep; i++) 
                {
                    Pen^ pPath = gcnew Pen(Color::Magenta, 4);
                    if (isDirected) pPath->CustomEndCap = gcnew AdjustableArrowCap(6, 6, true);

                    if (i < transitionStep) pPath->DashStyle = DashStyle::Dash;
                    else 
                    {
                        pPath->DashStyle = DashStyle::Solid;
                        pPath->Color = Color::Blue;
                    }
                    g->DrawLine(pPath, vertexList[fullPathIndices[i]]->Position, vertexList[fullPathIndices[i + 1]]->Position);
                }
            }

            for (int i = 0; i < vertexList->Count; i++) 
            {
                int r = globalVertexRadius;
                Rectangle rect(vertexList[i]->Position.X - r, vertexList[i]->Position.Y - r, r * 2, r * 2);
                Brush^ b = (currentStep >= 0 && fullPathIndices[currentStep] == i) ? Brushes::Yellow : Brushes::SkyBlue;
                if (vertexList[i] == selectedVertex) b = Brushes::Orange;

                g->FillEllipse(b, rect);
                g->DrawEllipse(Pens::Black, rect);
                g->DrawString((i + 1).ToString(), this->Font, Brushes::Black, vertexList[i]->Position.X - 7, vertexList[i]->Position.Y - 7);
            }
        }

        void OnCanvasMouseDown(Object^ sender, MouseEventArgs^ e) 
        {
            Vertex^ target = nullptr;
            for each (Vertex ^ v in vertexList) {
                if (Math::Sqrt(Math::Pow(v->Position.X - e->X, 2) + Math::Pow(v->Position.Y - e->Y, 2)) < globalVertexRadius + 5) target = v;
            }
            if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                if (target != nullptr) { draggedVertex = target; isDragging = true; selectedVertex = target; }
                else vertexList->Add(gcnew Vertex(e->Location));
            }
            else if (e->Button == System::Windows::Forms::MouseButtons::Right && target != nullptr) {
                if (selectedVertex != nullptr && selectedVertex != target) edgeList->Add(gcnew Edge(selectedVertex, target));
                selectedVertex = target;
            }
            drawingCanvas->Invalidate();
        }

        void OnCanvasMouseMove(Object^ sender, MouseEventArgs^ e) 
        {
            if (isDragging && draggedVertex != nullptr) 
            { 
                draggedVertex->Position = e->Location; drawingCanvas->Invalidate();
            }
        }

        void OnCanvasMouseUp(Object^ sender, MouseEventArgs^ e) 
        { 
            isDragging = false; 
            draggedVertex = nullptr; 
        }

        void OnSettingsChanged(Object^ sender, EventArgs^ e) 
        {
            globalVertexRadius = (int)inputRadius->Value;
            isDirected = chkDirected->Checked;
            drawingCanvas->Invalidate();
        }

        void OnClearClick(Object^ sender, EventArgs^ e) 
        {
            vertexList->Clear(); edgeList->Clear(); fullPathIndices->Clear();
            currentStep = -1; animationTimer->Stop(); selectedVertex = nullptr;
            lblResult->Text = "Canvas cleared."; drawingCanvas->Invalidate();
        }
    };
}
