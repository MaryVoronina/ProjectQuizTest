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

    public ref class Vertex {
    public:
        Point Position;
        Vertex(Point p) { Position = p; }
    };

    public ref class Edge {
    public:
        Vertex^ StartVertex;
        Vertex^ EndVertex;
        int Weight;
        Edge(Vertex^ start, Vertex^ end, int weight) {
            StartVertex = start;
            EndVertex = end;
            Weight = weight;
        }
    };

    public ref class quiz : public System::Windows::Forms::Form
    {
    private:
        List<Vertex^>^ vertexList;
        List<Edge^>^ edgeList;
        Vertex^ selectedVertex;
        Vertex^ draggedVertex;
        bool isDragging = false;

        bool isDirected = false;
        bool isWeighted = false;
        int globalVertexRadius = 15;
        Color globalVertexColor = Color::SkyBlue;
        Color globalEdgeColor = Color::Black;

        Panel^ drawingCanvas;
        MenuStrip^ mainMenu;
        ToolStripMenuItem^ itemDirected;
        ToolStripMenuItem^ itemWeighted;
        Label^ lblResult;
        NumericUpDown^ inputRadius;

    public:
        quiz(void) {
            InitializeComponent();
            vertexList = gcnew List<Vertex^>();
            edgeList = gcnew List<Edge^>();
            selectedVertex = nullptr;
        }

    private:
        void InitializeComponent(void) {
            //this->Text = L"Graph Designer - Euler Path Finder";
            this->Size = System::Drawing::Size(1000, 750);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(240, 240, 240);

            this->mainMenu = (gcnew MenuStrip());
            ToolStripMenuItem^ menuSettings = (gcnew ToolStripMenuItem(L"Settings"));

            this->itemDirected = (gcnew ToolStripMenuItem(L"Directed Mode", nullptr, gcnew EventHandler(this, &quiz::OnToggleSettings)));
            this->itemDirected->CheckOnClick = true;
            this->itemWeighted = (gcnew ToolStripMenuItem(L"Weighted Mode", nullptr, gcnew EventHandler(this, &quiz::OnToggleSettings)));
            this->itemWeighted->CheckOnClick = true;

            ToolStripMenuItem^ itemVertexColor = (gcnew ToolStripMenuItem(L"Vertex Color", nullptr, gcnew EventHandler(this, &quiz::OnPickVertexColor)));
            ToolStripMenuItem^ itemEdgeColor = (gcnew ToolStripMenuItem(L"Edge Color", nullptr, gcnew EventHandler(this, &quiz::OnPickEdgeColor)));

            menuSettings->DropDownItems->Add(this->itemDirected);
            menuSettings->DropDownItems->Add(this->itemWeighted);
            menuSettings->DropDownItems->Add(gcnew ToolStripSeparator());
            menuSettings->DropDownItems->Add(itemVertexColor);
            menuSettings->DropDownItems->Add(itemEdgeColor);
            this->mainMenu->Items->Add(menuSettings);
            this->Controls->Add(this->mainMenu);


            Panel^ centerContainer = gcnew Panel();
            centerContainer->Size = System::Drawing::Size(860, 620);
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
            controlsPanel->Size = System::Drawing::Size(840, 100);
            controlsPanel->Location = Point(10, 490);
            centerContainer->Controls->Add(controlsPanel);

            this->inputRadius = gcnew NumericUpDown();
            this->inputRadius->Location = Point(100, 13);
            this->inputRadius->Value = 15;
            this->inputRadius->ValueChanged += gcnew EventHandler(this, &quiz::OnToggleSettings);
            controlsPanel->Controls->Add(this->inputRadius);

            Label^ lblRad = gcnew Label();
            lblRad->Text = "Radius:";
            lblRad->Location = Point(40, 15);
            controlsPanel->Controls->Add(lblRad);

            Button^ btnEuler = gcnew Button();
            btnEuler->Text = L"FIND EULER PATH";
            btnEuler->Size = System::Drawing::Size(150, 40);
            btnEuler->Location = Point(0, 50);
            btnEuler->BackColor = Color::LightGreen;
            btnEuler->FlatStyle = FlatStyle::Flat;
            btnEuler->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold));
            btnEuler->Click += gcnew EventHandler(this, &quiz::OnEulerClick);
            controlsPanel->Controls->Add(btnEuler);

            Button^ btnClear = gcnew Button();
            btnClear->Text = L"CLEAR";
            btnClear->Size = System::Drawing::Size(150, 40);
            btnClear->Location = Point(160, 50);
            btnClear->BackColor = Color::LightSalmon;
            btnClear->FlatStyle = FlatStyle::Flat;
            btnClear->Click += gcnew EventHandler(this, &quiz::OnClearClick);
            controlsPanel->Controls->Add(btnClear);

            this->lblResult = gcnew Label();
            //this->lblResult->Text = L"L-Click: Add | Ctrl+L-Click: Delete | R-Click: Link";
            this->lblResult->Location = Point(330, 60);
            this->lblResult->AutoSize = true;
            this->lblResult->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold));
            controlsPanel->Controls->Add(this->lblResult);
        }

        int GetDegree(Vertex^ v) 
        {
            int deg = 0;
            for (int i = 0; i < edgeList->Count; i++) 
            {
                if (edgeList[i]->StartVertex == v || edgeList[i]->EndVertex == v) 
                    deg++;
            }
            return deg;
        }

        void OnEulerClick(Object^ sender, EventArgs^ e) 
        {
            if (vertexList->Count == 0 || edgeList->Count == 0) return;

            List<Vertex^>^ oddVertices = gcnew List<Vertex^>();
            for (int i = 0; i < vertexList->Count; i++) 
            {
                if (GetDegree(vertexList[i]) % 2 != 0) 
                    oddVertices->Add(vertexList[i]);
            }

            if (oddVertices->Count != 0 && oddVertices->Count != 2) 
            {
                lblResult->ForeColor = Color::Red;
                lblResult->Text = "No Euler path!";
                return;
            }

            
            List<Edge^>^ tempEdges = gcnew List<Edge^>(edgeList);
            Stack<Vertex^>^ st = gcnew Stack<Vertex^>();
            List<int>^ path = gcnew List<int>();
            Vertex^ current;

            if (oddVertices->Count == 2) 
            {
                current = oddVertices[0];
            }
            else 
            {
                current = vertexList[0];
            }

            st->Push(current);

            while (st->Count > 0) 
            {
                Vertex^ v = st->Peek();
                Edge^ foundEdge = nullptr;
                int edgeIdx = -1;

                for (int i = 0; i < tempEdges->Count && foundEdge == nullptr; i++) 
                {
                    if (tempEdges[i]->StartVertex == v) 
                    {
                        foundEdge = tempEdges[i];
                        edgeIdx = i;
                    }
                    else if (!isDirected && tempEdges[i]->EndVertex == v) 
                    {
                        foundEdge = tempEdges[i];
                        edgeIdx = i;
                    }
                }

                if (foundEdge != nullptr) 
                {
                    Vertex^ nextV;

                    if (foundEdge->StartVertex == v) 
                    {
                        nextV = foundEdge->EndVertex;
                    }
                    else 
                    {
                        nextV = foundEdge->StartVertex;
                    }

                    tempEdges->RemoveAt(edgeIdx);
                    st->Push(nextV);
                }
                else 
                {
                    path->Add(vertexList->IndexOf(st->Pop()) + 1);
                }
            }

            path->Reverse();
            lblResult->ForeColor = Color::DarkGreen;
            lblResult->Text = "Path: " + String::Join(" -> ", path);
        }

        void OnClearClick(Object^ sender, EventArgs^ e) 
        {
            vertexList->Clear(); 
            edgeList->Clear(); 
            selectedVertex = nullptr;
            lblResult->ForeColor = Color::Black; 
            lblResult->Text = "Canvas cleared.";
            drawingCanvas->Invalidate();
        }

        void OnPickVertexColor(Object^ sender, EventArgs^ e) 
        {
            ColorDialog^ cd = gcnew ColorDialog();
            if (cd->ShowDialog() == System::Windows::Forms::DialogResult::OK) 
            {
                globalVertexColor = cd->Color;
                drawingCanvas->Invalidate();
            }
        }

        void OnPickEdgeColor(Object^ sender, EventArgs^ e) 
        {
            ColorDialog^ cd = gcnew ColorDialog();
            if (cd->ShowDialog() == System::Windows::Forms::DialogResult::OK) 
            {
                globalEdgeColor = cd->Color;
                drawingCanvas->Invalidate();
            }
        }

        void OnCanvasMouseDown(Object^ sender, MouseEventArgs^ e) 
        {
            Vertex^ target = nullptr;
            int targetIdx = -1;
            for (int i = 0; i < vertexList->Count && target == nullptr; i++) 
            {
                double dist = Math::Sqrt(Math::Pow(vertexList[i]->Position.X - e->X, 2) + Math::Pow(vertexList[i]->Position.Y - e->Y, 2));
                if (dist < globalVertexRadius + 5) 
                { 
                    target = vertexList[i];
                    targetIdx = i; 
                }
            }

            if (e->Button == System::Windows::Forms::MouseButtons::Left && Control::ModifierKeys == Keys::Control) 
            {
                if (target != nullptr) 
                {
                    for (int i = edgeList->Count - 1; i >= 0; i--) 
                    {
                        if (edgeList[i]->StartVertex == target || edgeList[i]->EndVertex == target) 
                            edgeList->RemoveAt(i);
                    }
                    vertexList->RemoveAt(targetIdx);
                }
                else 
                {
                    bool removed = false;
                    for (int i = edgeList->Count - 1; i >= 0 && !removed; i--) {

                        Point mid((edgeList[i]->StartVertex->Position.X + edgeList[i]->EndVertex->Position.X) / 2, (edgeList[i]->StartVertex->Position.Y + edgeList[i]->EndVertex->Position.Y) / 2);
                        if (Math::Sqrt(Math::Pow(mid.X - e->X, 2) + Math::Pow(mid.Y - e->Y, 2)) < 15) 
                        { 
                            edgeList->RemoveAt(i); 
                            removed = true;
                        }
                    }
                }
            }
            else if (e->Button == System::Windows::Forms::MouseButtons::Left) 
            {
                if (target != nullptr) 
                { 
                    draggedVertex = target; 
                    isDragging = true; 
                    selectedVertex = target; 
                }
                else 
                { 
                    vertexList->Add(gcnew Vertex(e->Location)); 
                }
            }
            else if (e->Button == System::Windows::Forms::MouseButtons::Right && target != nullptr) 
            {
                if (selectedVertex != nullptr && selectedVertex != target) 
                {
                    edgeList->Add(gcnew Edge(selectedVertex, target, 1));
                    selectedVertex = nullptr;
                }
                else selectedVertex = target;
            }
            drawingCanvas->Invalidate();
        }

        void OnCanvasPaint(Object^ sender, PaintEventArgs^ e) 
        {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::AntiAlias;
            Pen^ p = gcnew Pen(globalEdgeColor, 2);

            for (int i = 0; i < edgeList->Count; i++) 
            {
                Point pS = edgeList[i]->StartVertex->Position;
                Point pE = edgeList[i]->EndVertex->Position;
                double dx = pE.X - pS.X;
                double dy = pE.Y - pS.Y;
                double len = Math::Sqrt(dx * dx + dy * dy);
                if (len > 0) 
                {
                    Point arrowT = Point(pE.X - (int)((dx / len) * globalVertexRadius), pE.Y - (int)((dy / len) * globalVertexRadius));
                    if (isDirected) 
                        p->CustomEndCap = gcnew AdjustableArrowCap(5, 5, true);
                    else p->EndCap = LineCap::Flat;
                    g->DrawLine(p, pS, arrowT);
                }
            }

            for (int i = 0; i < vertexList->Count; i++) 
            {
                int r = globalVertexRadius;
                Rectangle rect(vertexList[i]->Position.X - r, vertexList[i]->Position.Y - r, r * 2, r * 2);
                Brush^ b;
                if (vertexList[i] == selectedVertex) 
                {
                    b = Brushes::Orange;
                }
                else 
                {
                    b = gcnew SolidBrush(globalVertexColor);
                }

                g->FillEllipse(b, rect);                
                g->DrawEllipse(Pens::Black, rect);
                String^ name = (i + 1).ToString();
                SizeF sz = g->MeasureString(name, this->Font);
                g->DrawString(name, this->Font, Brushes::Black, vertexList[i]->Position.X - sz.Width / 2, vertexList[i]->Position.Y - sz.Height / 2);
            }
        }

        void OnCanvasMouseMove(Object^ sender, MouseEventArgs^ e) 
        {
            if (isDragging && draggedVertex != nullptr) 
            { 
                draggedVertex->Position = e->Location; 
                drawingCanvas->Invalidate();
            }
        }

        void OnCanvasMouseUp(Object^ sender, MouseEventArgs^ e) 
        { 
            isDragging = false; 
            draggedVertex = nullptr; 
        }

        void OnToggleSettings(Object^ sender, EventArgs^ e) 
        {
            isDirected = itemDirected->Checked;
            isWeighted = itemWeighted->Checked;
            globalVertexRadius = (int)inputRadius->Value;
            drawingCanvas->Invalidate();
        }
    };
}
