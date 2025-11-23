#pragma once

namespace ProjectQuizTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для quiz
	/// </summary>
	public ref class quiz : public System::Windows::Forms::Form
	{
	public:
		quiz(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			currentQuestion = 0;
			correctCount = 0;

			open_file();
			// load_info();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~quiz()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Button^ button_next;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox4;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

		System::Collections::Generic::List<String^>^ questions;
		System::Collections::Generic::List<System::Collections::Generic::List<String^>^>^ answers;
		System::Collections::Generic::List<System::Collections::Generic::List<String^>^>^ correctAnswers;
		System::Collections::Generic::List<bool>^ isMultipleChoice;
		int currentQuestion;
		String^ userName;
	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::FlowLayoutPanel^ start_panel;
	private: System::Windows::Forms::Label^ label_write_name;


	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
		   int correctCount;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Требуемый метод для поддержки конструктора — не изменяйте 
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			   this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			   this->button_next = (gcnew System::Windows::Forms::Button());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->start_panel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->label_write_name = (gcnew System::Windows::Forms::Label());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->flowLayoutPanel1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->start_panel->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(382, 85);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(51, 20);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"label1";
			   this->label1->Visible = false;
			   // 
			   // flowLayoutPanel1
			   // 
			   this->flowLayoutPanel1->Controls->Add(this->checkBox1);
			   this->flowLayoutPanel1->Controls->Add(this->checkBox2);
			   this->flowLayoutPanel1->Controls->Add(this->checkBox3);
			   this->flowLayoutPanel1->Controls->Add(this->checkBox4);
			   this->flowLayoutPanel1->Controls->Add(this->checkBox5);
			   this->flowLayoutPanel1->Location = System::Drawing::Point(384, 165);
			   this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			   this->flowLayoutPanel1->Size = System::Drawing::Size(193, 442);
			   this->flowLayoutPanel1->TabIndex = 1;
			   this->flowLayoutPanel1->Visible = false;
			   // 
			   // checkBox1
			   // 
			   this->checkBox1->AutoSize = true;
			   this->checkBox1->Location = System::Drawing::Point(3, 3);
			   this->checkBox1->Name = L"checkBox1";
			   this->checkBox1->Size = System::Drawing::Size(113, 24);
			   this->checkBox1->TabIndex = 0;
			   this->checkBox1->Text = L"checkBox1";
			   this->checkBox1->UseVisualStyleBackColor = true;
			   this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &quiz::checkBox1_CheckedChanged);
			   // 
			   // checkBox2
			   // 
			   this->checkBox2->AutoSize = true;
			   this->checkBox2->Location = System::Drawing::Point(3, 33);
			   this->checkBox2->Name = L"checkBox2";
			   this->checkBox2->Size = System::Drawing::Size(113, 24);
			   this->checkBox2->TabIndex = 1;
			   this->checkBox2->Text = L"checkBox2";
			   this->checkBox2->UseVisualStyleBackColor = true;
			   this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &quiz::checkBox2_CheckedChanged);
			   // 
			   // checkBox3
			   // 
			   this->checkBox3->AutoSize = true;
			   this->checkBox3->Location = System::Drawing::Point(3, 63);
			   this->checkBox3->Name = L"checkBox3";
			   this->checkBox3->Size = System::Drawing::Size(113, 24);
			   this->checkBox3->TabIndex = 2;
			   this->checkBox3->Text = L"checkBox3";
			   this->checkBox3->UseVisualStyleBackColor = true;
			   this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &quiz::checkBox3_CheckedChanged);
			   // 
			   // checkBox4
			   // 
			   this->checkBox4->AutoSize = true;
			   this->checkBox4->Location = System::Drawing::Point(3, 93);
			   this->checkBox4->Name = L"checkBox4";
			   this->checkBox4->Size = System::Drawing::Size(113, 24);
			   this->checkBox4->TabIndex = 3;
			   this->checkBox4->Text = L"checkBox4";
			   this->checkBox4->UseVisualStyleBackColor = true;
			   this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &quiz::checkBox4_CheckedChanged);
			   // 
			   // checkBox5
			   // 
			   this->checkBox5->AutoSize = true;
			   this->checkBox5->Location = System::Drawing::Point(3, 123);
			   this->checkBox5->Name = L"checkBox5";
			   this->checkBox5->Size = System::Drawing::Size(113, 24);
			   this->checkBox5->TabIndex = 4;
			   this->checkBox5->Text = L"checkBox5";
			   this->checkBox5->UseVisualStyleBackColor = true;
			   this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &quiz::checkBox5_CheckedChanged);
			   // 
			   // button_next
			   // 
			   this->button_next->Location = System::Drawing::Point(398, 657);
			   this->button_next->Name = L"button_next";
			   this->button_next->Size = System::Drawing::Size(150, 75);
			   this->button_next->TabIndex = 2;
			   this->button_next->Text = L"Next";
			   this->button_next->UseVisualStyleBackColor = true;
			   this->button_next->Visible = false;
			   this->button_next->Click += gcnew System::EventHandler(this, &quiz::button_next_Click);
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(388, 622);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(51, 20);
			   this->label2->TabIndex = 3;
			   this->label2->Text = L"label2";
			   this->label2->Visible = false;
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(686, 105);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(390, 183);
			   this->pictureBox1->TabIndex = 4;
			   this->pictureBox1->TabStop = false;
			   // 
			   // start_panel
			   // 
			   this->start_panel->Controls->Add(this->label_write_name);
			   this->start_panel->Controls->Add(this->textBox1);
			   this->start_panel->Controls->Add(this->button1);
			   this->start_panel->Location = System::Drawing::Point(554, 294);
			   this->start_panel->Name = L"start_panel";
			   this->start_panel->Size = System::Drawing::Size(832, 439);
			   this->start_panel->TabIndex = 5;
			   // 
			   // label_write_name
			   // 
			   this->label_write_name->AutoSize = true;
			   this->label_write_name->Location = System::Drawing::Point(3, 0);
			   this->label_write_name->Name = L"label_write_name";
			   this->label_write_name->Size = System::Drawing::Size(144, 20);
			   this->label_write_name->TabIndex = 0;
			   this->label_write_name->Text = L"Введіть ваше ім\'я";
			   this->label_write_name->Click += gcnew System::EventHandler(this, &quiz::label3_Click);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(153, 3);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(552, 26);
			   this->textBox1->TabIndex = 1;
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->button1->Location = System::Drawing::Point(3, 35);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(176, 58);
			   this->button1->TabIndex = 2;
			   this->button1->Text = L"Start";
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &quiz::button1_Click);
			   // 
			   // quiz
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1712, 860);
			   this->Controls->Add(this->start_panel);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->button_next);
			   this->Controls->Add(this->flowLayoutPanel1);
			   this->Controls->Add(this->label1);
			   this->Name = L"quiz";
			   this->Text = L"quiz";
			   this->flowLayoutPanel1->ResumeLayout(false);
			   this->flowLayoutPanel1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->start_panel->ResumeLayout(false);
			   this->start_panel->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: int get_num_marks() 
	{
		int count = 0;
		array<CheckBox^>^ checkBoxes = { checkBox1, checkBox2, checkBox3, checkBox4, checkBox5 };
		for (int i = 0; i < checkBoxes->Length; i++)
		{
			if (checkBoxes[i]->Visible && checkBoxes[i]->Checked) {
				count++;
			}
		}
		return count;
	}

	private: System::Void button_next_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (get_num_marks() == 0)
		{
			MessageBox::Show("Ви повинні обрати хоча б одну відповідь!", "Увага");
			return;
		}

		System::Collections::Generic::List<String^>^ selected = gcnew System::Collections::Generic::List<String^>();

		if (checkBox1->Visible && checkBox1->Checked)
		{
			selected->Add("A");
		}
		if (checkBox2->Visible && checkBox2->Checked)
		{
			selected->Add("B");
		}
		if (checkBox3->Visible && checkBox3->Checked)
		{
			selected->Add("C");
		}
		if (checkBox4->Visible && checkBox4->Checked)
		{
			selected->Add("D");
		}
		if (checkBox5->Visible && checkBox5->Checked)
		{
			selected->Add("E");
		}

		bool isCorrect = true;

		for (int i = 0; i < selected->Count; i++)
		{
			if (!correctAnswers[currentQuestion]->Contains(selected[i]))
			{
				isCorrect = false;
				break;
			}
		}

		if (isCorrect && selected->Count != correctAnswers[currentQuestion]->Count)
		{
			isCorrect = false;
		}

		if (isCorrect)
		{
			correctCount++;
		}

		currentQuestion++;
		if (currentQuestion < questions->Count) {
			load_info();
		}
		else
		{
			String^ result = String::Format("Правильних відповідей: {0}", correctCount, questions->Count);
			MessageBox::Show(result, "Результат тесту", MessageBoxButtons::OK, MessageBoxIcon::Information);
			save_result(); // Зберігаємо результат
			Application::Exit();
		}
	}

		   void open_file()
		   {
			   array<String^>^ lines = System::IO::File::ReadAllLines("quiz_questions.txt", System::Text::Encoding::UTF8);

			   questions = gcnew System::Collections::Generic::List<String^>();
			   answers = gcnew System::Collections::Generic::List<System::Collections::Generic::List<String^>^>();
			   correctAnswers = gcnew System::Collections::Generic::List<System::Collections::Generic::List<String^>^>();
			   isMultipleChoice = gcnew System::Collections::Generic::List<bool>();

			   System::Collections::Generic::List<String^>^ options = gcnew System::Collections::Generic::List<String^>();

			   System::Collections::Generic::List<String^>^ correct = gcnew System::Collections::Generic::List<String^>();

			   for (int i = 0; i < lines->Length; i++)
			   {
				   if (String::IsNullOrEmpty(lines[i]))
					   continue;

				   char first_char = lines[i][0];
				   if (first_char >= '0' && first_char <= '9')
				   {
					   questions->Add(lines[i]);
				   }
				   else if (first_char >= 'A' && first_char <= 'E' && lines[i][1] == '.')
				   {
					   options->Add(lines[i]);
				   }
				   else if (lines[i]->StartsWith("Correct"))
				   {
					   answers->Add(options);

					   String^ correctStr = lines[i]->Substring(9)->Trim();
					   array<String^>^ correctLetters = correctStr->Split(' ');

					   for each(String ^ letter in correctLetters)
					   {
						   if (!String::IsNullOrEmpty(letter->Trim()))
						   {
							   correct->Add(letter->Trim());
						   }
					   }

					   correctAnswers->Add(correct);
					   isMultipleChoice->Add(correct->Count > 1);

					   options = gcnew System::Collections::Generic::List<String^>();
					   correct = gcnew System::Collections::Generic::List<String^>();
				   }
			   }
		   }
		   void load_info()
		   {
			   label1->Text = questions[currentQuestion];

			   System::Collections::Generic::List<String^>^ currentAnswers = answers[currentQuestion];
			   int count = currentAnswers->Count;
			   array<CheckBox^>^ checkBoxes = { checkBox1, checkBox2, checkBox3, checkBox4, checkBox5 };
			   for (int i = 0; i < checkBoxes->Length; i++)
			   {
				   if (i < count)
				   {
					   checkBoxes[i]->Visible = true;
					   checkBoxes[i]->Text = currentAnswers[i];
				   }
				   else
				   {
					   checkBoxes[i]->Visible = false;
				   }
				   checkBoxes[i]->Checked = false;
			   }

			   if (isMultipleChoice[currentQuestion])
			   {
				   label2->Text = L"Можна обрати кілька відповідей";
			   }
			   else
			   {
				   label2->Text = L"Оберіть тільки одну відповідь";
			   }

			   // currentQuestion = 5
			   if (currentQuestion == 5) 
			   {
				   pictureBox1->Load("Image20251120181827.jpg");
				   pictureBox1->Visible = true;
			   }
			   else 
			   {
				   pictureBox1->Visible = false;
			   }
		   }


	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		userName = textBox1->Text->Trim();
		start_panel->Visible = false;
		flowLayoutPanel1->Visible = true;
		label1->Visible = true;
		label2->Visible = true;
		button_next->Visible = true;
		load_info();
	}

	private: void check(System::Object^ sender)
	{
		CheckBox^ currentCheckBox = safe_cast<CheckBox^>(sender);
		if (isMultipleChoice[currentQuestion] || !currentCheckBox->Checked) 
		{
			return;
		}
		int count = get_num_marks();
		if (count == 1) 
		{
			return;
		}
		else 
		{
			currentCheckBox->Checked = false;
			MessageBox::Show("Можна вибрати лише одну відповідь!", "Увага");
		}
	}

	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		check(sender);
	}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		check(sender);
	}
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		check(sender);
	}
	private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		check(sender);
	}
	private: System::Void checkBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		check(sender);
	}

		   void save_result() {
			   System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(
				   "results.txt", true, System::Text::Encoding::UTF8);

			   String^ timestamp = System::DateTime::Now.ToString("dd.MM.yyyy HH:mm:ss");
			   String^ result = String::Format("{0} - {1}: {2}/{3}",
				   timestamp, userName, correctCount, questions->Count);

			   writer->WriteLine(result);
			   writer->Close();
		   }

	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
