#pragma once

#include <msclr/marshal.h>

extern "C" {
#include "../src/vgmstream.h"
#include "../src/util.h"
}

namespace exportloop_gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	using namespace msclr::interop;
	using DR = System::Windows::Forms::DialogResult;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	internal: System::Windows::Forms::Button^  btnRemove;
	protected:
	internal: System::Windows::Forms::Button^  btnAdd;
	internal: System::Windows::Forms::ListView^  listView1;

	internal: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;

	internal: System::Windows::Forms::Button^  btnStart;
	internal: System::Windows::Forms::Button^  btnBrowse;
	internal: System::Windows::Forms::TextBox^  txtOutputDir;
	internal: System::Windows::Forms::Label^  Label1;
	internal: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	internal: System::Windows::Forms::Button^  btnAbout;
	internal: System::Windows::Forms::CheckBox^  chk0ToEnd;
	internal: System::Windows::Forms::CheckBox^  chkStartToEnd;
	internal: System::Windows::Forms::Label^  Label2;
	internal: System::Windows::Forms::CheckBox^  chk0ToStart;
	internal: System::Windows::Forms::Button^  btnOpenFolder;

	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnRemove = (gcnew System::Windows::Forms::Button());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->txtOutputDir = (gcnew System::Windows::Forms::TextBox());
			this->Label1 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnAbout = (gcnew System::Windows::Forms::Button());
			this->chk0ToEnd = (gcnew System::Windows::Forms::CheckBox());
			this->chkStartToEnd = (gcnew System::Windows::Forms::CheckBox());
			this->Label2 = (gcnew System::Windows::Forms::Label());
			this->chk0ToStart = (gcnew System::Windows::Forms::CheckBox());
			this->btnOpenFolder = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnRemove
			// 
			this->btnRemove->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnRemove->Location = System::Drawing::Point(297, 41);
			this->btnRemove->Name = L"btnRemove";
			this->btnRemove->Size = System::Drawing::Size(75, 23);
			this->btnRemove->TabIndex = 15;
			this->btnRemove->Text = L"Remove";
			this->btnRemove->UseVisualStyleBackColor = true;
			this->btnRemove->Click += gcnew System::EventHandler(this, &MainForm::btnRemove_Click);
			// 
			// btnAdd
			// 
			this->btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnAdd->Location = System::Drawing::Point(297, 12);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(75, 23);
			this->btnAdd->TabIndex = 14;
			this->btnAdd->Text = L"Add";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &MainForm::btnAdd_Click);
			// 
			// listView1
			// 
			this->listView1->AllowDrop = true;
			this->listView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listView1->Location = System::Drawing::Point(12, 12);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(279, 187);
			this->listView1->TabIndex = 13;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			this->listView1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::listView1_DragDrop);
			this->listView1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::listView1_DragEnter);
			// 
			// btnStart
			// 
			this->btnStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnStart->Location = System::Drawing::Point(297, 326);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 25;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MainForm::btnStart_Click);
			// 
			// btnBrowse
			// 
			this->btnBrowse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnBrowse->Location = System::Drawing::Point(266, 299);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(50, 21);
			this->btnBrowse->TabIndex = 22;
			this->btnBrowse->Text = L"Browse";
			this->btnBrowse->UseVisualStyleBackColor = true;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &MainForm::btnBrowse_Click);
			// 
			// txtOutputDir
			// 
			this->txtOutputDir->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputDir->Location = System::Drawing::Point(103, 300);
			this->txtOutputDir->Name = L"txtOutputDir";
			this->txtOutputDir->Size = System::Drawing::Size(157, 20);
			this->txtOutputDir->TabIndex = 21;
			// 
			// Label1
			// 
			this->Label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Label1->Location = System::Drawing::Point(12, 300);
			this->Label1->Margin = System::Windows::Forms::Padding(3);
			this->Label1->Name = L"Label1";
			this->Label1->Size = System::Drawing::Size(85, 20);
			this->Label1->TabIndex = 20;
			this->Label1->Text = L"Output directory:";
			this->Label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Multiselect = true;
			// 
			// btnAbout
			// 
			this->btnAbout->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnAbout->Location = System::Drawing::Point(12, 326);
			this->btnAbout->Name = L"btnAbout";
			this->btnAbout->Size = System::Drawing::Size(75, 23);
			this->btnAbout->TabIndex = 24;
			this->btnAbout->Text = L"About";
			this->btnAbout->UseVisualStyleBackColor = true;
			this->btnAbout->Click += gcnew System::EventHandler(this, &MainForm::btnAbout_Click);
			// 
			// chk0ToEnd
			// 
			this->chk0ToEnd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->chk0ToEnd->AutoSize = true;
			this->chk0ToEnd->Checked = true;
			this->chk0ToEnd->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chk0ToEnd->Location = System::Drawing::Point(15, 277);
			this->chk0ToEnd->Name = L"chk0ToEnd";
			this->chk0ToEnd->Size = System::Drawing::Size(168, 17);
			this->chk0ToEnd->TabIndex = 19;
			this->chk0ToEnd->Text = L"Song start to end (entire song)";
			this->chk0ToEnd->UseVisualStyleBackColor = true;
			// 
			// chkStartToEnd
			// 
			this->chkStartToEnd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->chkStartToEnd->AutoSize = true;
			this->chkStartToEnd->Checked = true;
			this->chkStartToEnd->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkStartToEnd->Location = System::Drawing::Point(15, 254);
			this->chkStartToEnd->Name = L"chkStartToEnd";
			this->chkStartToEnd->Size = System::Drawing::Size(106, 17);
			this->chkStartToEnd->TabIndex = 18;
			this->chkStartToEnd->Text = L"Loop start to end";
			this->chkStartToEnd->UseVisualStyleBackColor = true;
			// 
			// Label2
			// 
			this->Label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Label2->Location = System::Drawing::Point(12, 205);
			this->Label2->Margin = System::Windows::Forms::Padding(3);
			this->Label2->Name = L"Label2";
			this->Label2->Size = System::Drawing::Size(85, 20);
			this->Label2->TabIndex = 16;
			this->Label2->Text = L"Files to export:";
			this->Label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// chk0ToStart
			// 
			this->chk0ToStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->chk0ToStart->AutoSize = true;
			this->chk0ToStart->Location = System::Drawing::Point(15, 231);
			this->chk0ToStart->Name = L"chk0ToStart";
			this->chk0ToStart->Size = System::Drawing::Size(132, 17);
			this->chk0ToStart->TabIndex = 17;
			this->chk0ToStart->Text = L"Song start to loop start";
			this->chk0ToStart->UseVisualStyleBackColor = true;
			// 
			// btnOpenFolder
			// 
			this->btnOpenFolder->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btnOpenFolder->Location = System::Drawing::Point(322, 299);
			this->btnOpenFolder->Name = L"btnOpenFolder";
			this->btnOpenFolder->Size = System::Drawing::Size(50, 21);
			this->btnOpenFolder->TabIndex = 23;
			this->btnOpenFolder->Text = L"Open";
			this->btnOpenFolder->UseVisualStyleBackColor = true;
			this->btnOpenFolder->Click += gcnew System::EventHandler(this, &MainForm::btnOpenFolder_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 361);
			this->Controls->Add(this->btnRemove);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->btnBrowse);
			this->Controls->Add(this->txtOutputDir);
			this->Controls->Add(this->Label1);
			this->Controls->Add(this->btnAbout);
			this->Controls->Add(this->chk0ToEnd);
			this->Controls->Add(this->chkStartToEnd);
			this->Controls->Add(this->Label2);
			this->Controls->Add(this->chk0ToStart);
			this->Controls->Add(this->btnOpenFolder);
			this->Name = L"MainForm";
			this->Text = L"BRSTM to WAV Converter";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		void btnAdd_Click(Object^ sender, EventArgs^ e) {
			if (openFileDialog1->ShowDialog() == DR::OK) {
				for each (String^ f in openFileDialog1->FileNames) {
					listView1->Items->Add(f);
				}
			}
		}
		void btnRemove_Click(Object^ sender, EventArgs^ e) {
			for each (ListViewItem^ item in listView1->SelectedItems) {
				listView1->Items->Remove(item);
			}
		}
		void listView1_DragEnter(Object^ sender, DragEventArgs^ e) {
			if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
				e->Effect = DragDropEffects::Link;
			}
		}
		void listView1_DragDrop(Object^ sender, DragEventArgs^ e) {
			if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
				array<String^>^ filenames = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
				for each (String^ filename in filenames) {
					listView1->Items->Add(filename);
				}
			}
		}
		void btnBrowse_Click(Object^ sender, EventArgs^ e) {
			if (!String::IsNullOrWhiteSpace(txtOutputDir->Text)) {
				folderBrowserDialog1->SelectedPath = txtOutputDir->Text;
			}
			if (folderBrowserDialog1->ShowDialog() == DR::OK) {
				txtOutputDir->Text = folderBrowserDialog1->SelectedPath;
			}
		}
		void btnOpenFolder_Click(Object^ sender, EventArgs^ e) {
			MessageBox::Show("Not implemented");
		}
		void btnAbout_Click(Object^ sender, EventArgs^ e) {
			MessageBox::Show("BRSTM to WAV Converter 2.0\n"
				"© 2015 libertyernie\n"
				"\n"
				"https://github.com/libertyernie/vgmstream\n"
				"\n"
				"TODO: put license here. All rights reserved.");
		}
		void btnStart_Click(Object^ sender, EventArgs^ e) {
			String^ outputDir = txtOutputDir->Text;
			if (!Directory::Exists(outputDir)) {
				MessageBox::Show("The specified output directory does not exist.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			marshal_context context;

			for each (ListViewItem^ item in listView1->Items) {
				String^ inputpath = item->Text;
				VGMSTREAM* vgmstream = init_vgmstream(context.marshal_as<const char*>(inputpath));

				if (vgmstream == NULL) {
					MessageBox::Show("Could not open file: " + inputpath, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					continue;
				}

				sample* samples = (sample*)malloc(sizeof(sample) * vgmstream->channels * vgmstream->num_samples);
				render_vgmstream(samples, vgmstream->num_samples, vgmstream);
				swap_samples_le(samples, vgmstream->channels * vgmstream->num_samples);

				uint8_t* wavbuffer = (uint8_t*)malloc(0x2C);

				String^ filename_without_ext = Path::GetFileNameWithoutExtension(inputpath);

				if (chk0ToStart->Checked) {
					String^ outputfile = filename_without_ext + " (beginning).wav";

					FILE* f = fopen(context.marshal_as<const char*>(outputfile), "wb");
					make_wav_header(wavbuffer,
						vgmstream->loop_start_sample,
						vgmstream->sample_rate,
						vgmstream->channels);
					fwrite(wavbuffer, 0x2C, 1, f);
					fwrite(samples,
						sizeof(sample),
						vgmstream->loop_start_sample * vgmstream->channels,
						f);
					fclose(f);
				}
				if (chkStartToEnd->Checked) {
					String^ outputfile = filename_without_ext + " (loop).wav";

					FILE* f = fopen(context.marshal_as<const char*>(outputfile), "wb");
					make_wav_header(wavbuffer,
						vgmstream->loop_end_sample - vgmstream->loop_start_sample,
						vgmstream->sample_rate,
						vgmstream->channels);
					fwrite(wavbuffer, 0x2C, 1, f);
					fwrite(samples + vgmstream->loop_start_sample * vgmstream->channels,
						sizeof(sample),
						(vgmstream->loop_end_sample - vgmstream->loop_start_sample) * vgmstream->channels,
						f);
					fclose(f);
				}
				if (chk0ToEnd->Checked) {
					String^ outputfile = filename_without_ext + " (beginning).wav";

					FILE* f = fopen(context.marshal_as<const char*>(outputfile), "wb");
					make_wav_header(wavbuffer,
						vgmstream->num_samples,
						vgmstream->sample_rate,
						vgmstream->channels);
					fwrite(wavbuffer, 0x2C, 1, f);
					fwrite(samples,
						sizeof(sample),
						vgmstream->num_samples * vgmstream->channels,
						f);
					fclose(f);
				}

				free(wavbuffer);
				free(samples);
				close_vgmstream(vgmstream);
			}
		}
	};
}
