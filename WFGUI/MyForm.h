#pragma once

#include "KinectV1Capture.h"

namespace WFGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	KinectV1Capture kinect;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox_Color;
	private: System::Windows::Forms::PictureBox^  pictureBox_Depth;
	protected:

	private: DoubleTrackBar^  DoubleTrackBar_DepthDistance;
	private: System::Windows::Forms::Label^  label_DepthMaxName;
	private: System::Windows::Forms::Label^  label_DepthMinName;
	private: System::Windows::Forms::Label^  label_DepthMinValue;
	private: System::Windows::Forms::Label^  label_DepthMaxValue;


	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::Threading::Thread^ Thr_Capture = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::QueryFrame));


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox_Color = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_Depth = (gcnew System::Windows::Forms::PictureBox());
			this->DoubleTrackBar_DepthDistance = (gcnew DoubleTrackBar());
			this->label_DepthMaxName = (gcnew System::Windows::Forms::Label());
			this->label_DepthMinName = (gcnew System::Windows::Forms::Label());
			this->label_DepthMinValue = (gcnew System::Windows::Forms::Label());
			this->label_DepthMaxValue = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Color))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Depth))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox_Color
			// 
			this->pictureBox_Color->Location = System::Drawing::Point(0, 0);
			this->pictureBox_Color->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox_Color->Name = L"pictureBox_Color";
			this->pictureBox_Color->Size = System::Drawing::Size(640, 480);
			this->pictureBox_Color->TabIndex = 4;
			this->pictureBox_Color->TabStop = false;
			// 
			// pictureBox_Depth
			// 
			this->pictureBox_Depth->Location = System::Drawing::Point(640, 0);
			this->pictureBox_Depth->Name = L"pictureBox_Depth";
			this->pictureBox_Depth->Size = System::Drawing::Size(640, 480);
			this->pictureBox_Depth->TabIndex = 5;
			this->pictureBox_Depth->TabStop = false;
			// 
			// DoubleTrackBar_DepthDistance
			// 
			this->DoubleTrackBar_DepthDistance->Location = System::Drawing::Point(816, 495);
			this->DoubleTrackBar_DepthDistance->Maximum = 1000;
			this->DoubleTrackBar_DepthDistance->Minimum = 0;
			this->DoubleTrackBar_DepthDistance->Name = L"DoubleTrackBar_DepthDistance";
			this->DoubleTrackBar_DepthDistance->Size = System::Drawing::Size(272, 73);
			this->DoubleTrackBar_DepthDistance->SmallChange = 1;
			this->DoubleTrackBar_DepthDistance->TabIndex = 6;
			this->DoubleTrackBar_DepthDistance->Text = L"doubleTrackBar1";
			this->DoubleTrackBar_DepthDistance->ValueLeft = 0;
			this->DoubleTrackBar_DepthDistance->ValueRight = 1000;
			this->DoubleTrackBar_DepthDistance->LeftValueChanged += gcnew System::EventHandler(this, &MyForm::doubleTrackBar_DepthDistance_Scroll_Left);
			this->DoubleTrackBar_DepthDistance->RightValueChanged += gcnew System::EventHandler(this, &MyForm::doubleTrackBar_DepthDistance_Scroll_Right);
			// 
			// label_DepthMaxName
			// 
			this->label_DepthMaxName->AutoSize = true;
			this->label_DepthMaxName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label_DepthMaxName->Location = System::Drawing::Point(1168, 524);
			this->label_DepthMaxName->Name = L"label_DepthMaxName";
			this->label_DepthMaxName->Size = System::Drawing::Size(103, 22);
			this->label_DepthMaxName->TabIndex = 1;
			this->label_DepthMaxName->Text = L"Depth Max";
			// 
			// label_DepthMinName
			// 
			this->label_DepthMinName->AutoSize = true;
			this->label_DepthMinName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label_DepthMinName->Location = System::Drawing::Point(636, 524);
			this->label_DepthMinName->Name = L"label_DepthMinName";
			this->label_DepthMinName->Size = System::Drawing::Size(100, 22);
			this->label_DepthMinName->TabIndex = 0;
			this->label_DepthMinName->Text = L"Depth Min";
			// 
			// label_DepthMinValue
			// 
			this->label_DepthMinValue->AutoSize = true;
			this->label_DepthMinValue->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label_DepthMinValue->Location = System::Drawing::Point(760, 524);
			this->label_DepthMinValue->Name = L"label_DepthMinValue";
			this->label_DepthMinValue->Size = System::Drawing::Size(20, 22);
			this->label_DepthMinValue->TabIndex = 7;
			this->label_DepthMinValue->Text = L"0";
			// 
			// label_DepthMaxValue
			// 
			this->label_DepthMaxValue->AutoSize = true;
			this->label_DepthMaxValue->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label_DepthMaxValue->Location = System::Drawing::Point(1111, 524);
			this->label_DepthMaxValue->Name = L"label_DepthMaxValue";
			this->label_DepthMaxValue->Size = System::Drawing::Size(50, 22);
			this->label_DepthMaxValue->TabIndex = 8;
			this->label_DepthMaxValue->Text = L"1000";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1283, 621);
			this->Controls->Add(this->label_DepthMaxValue);
			this->Controls->Add(this->label_DepthMinValue);
			this->Controls->Add(this->DoubleTrackBar_DepthDistance);
			this->Controls->Add(this->pictureBox_Depth);
			this->Controls->Add(this->pictureBox_Color);
			this->Controls->Add(this->label_DepthMaxName);
			this->Controls->Add(this->label_DepthMinName);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Color))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Depth))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void doubleTrackBar_DepthDistance_Scroll_Left(System::Object^ sender, System::EventArgs^ e) {
		label_DepthMinValue->Text = String::Concat("", DoubleTrackBar_DepthDistance->ValueLeft);
		kinect.SetMinDepth(DoubleTrackBar_DepthDistance->ValueLeft);
	}
	private: System::Void doubleTrackBar_DepthDistance_Scroll_Right(System::Object^ sender, System::EventArgs^ e) {
		label_DepthMaxValue->Text = String::Concat("", DoubleTrackBar_DepthDistance->ValueRight);
		kinect.SetMaxDepth(DoubleTrackBar_DepthDistance->ValueRight);
	}
		

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		Thr_Capture->Start();
	}

	private: void QueryFrame() {
		if (kinect.Init() != S_OK) {
			return;
		}

		cv::Mat ColorImg;
		cv::Mat DepthImg;
		
		ColorImg.create(kinect.GetColorImgSize(), kinect.GetColorImgType());
		DepthImg.create(kinect.GetColorImgSize(), kinect.GetColorImgType());
		
		while (1) {
			kinect.UpdateFrame();

			ColorImg = kinect.GetColorImg();
			DepthImg = kinect.GetDepth3HImg();

			pictureBox_Color->Image = gcnew Bitmap(ColorImg.cols, ColorImg.rows, ColorImg.step, Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) ColorImg.data);
			pictureBox_Depth->Image = gcnew Bitmap(DepthImg.cols, DepthImg.rows, DepthImg.step, Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) DepthImg.data);		
			
			Thr_Capture->Sleep(10);
		}
	}

	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		kinect.Close();
	}
};
}
