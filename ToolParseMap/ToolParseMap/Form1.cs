using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace ToolParseMap
{
    public partial class Form1 : Form
    {
        private string[] _fileLines;            // Các dòng trong file map có được từ tiled map
        private string _filePath;               //Đường dẫn đến file map có được từ tiled                  
        private int _numCol;                    //Số cột ma trận map
        private int _numRow;                    //Số dòng ma trận map
        private int _tilewidth;                 //Chiều dài 1 tile
        private int _tileheight;                //Chiều cao 1 tile
        private string[][] _mapMatrix;          //Ma trận map đã được chuyển đổi xong
        private int _currentRow ;               //Dòng hiện tại đang được đọc
        private int _maxEnemy = 20;             //Số lượng tank địch tối đa mặc định
        private int[] _numtank = new int[4];    //Số lượng tank địch từng loại: 1-Medium    2-Light     3-Heavy     4-SuperHeavy
        private string _order;             //Thứ tự nhóm tank địch xuất hiện
        //type Brick                //Số lượng từng loại gạch
        private int _numBrick1;
        private int _numBrick2;
        private int _numBrick11;
        private int _numBrick12;
        //type Steel                //Số lượng từng loại thép
        private int _numSteel3;
        private int _numSteel4;
        private int _numSteel13;
        private int _numSteel14;
        //type water                //Số lượng từng loại sông
        private int _numWater5;
        private int _numWater6;
        private int _numWater15;
        private int _numWater16;
        //type trees                //Số lượng từng loại rừng
        private int _numTrees7;
        private int _numTrees8;
        private int _numTrees17;
        private int _numTrees18;
        //type ice                  //Số lượng từng loại băng
        private int _numIce9;
        private int _numIce10;
        private int _numIce19;
        private int _numIce20;

        public Form1()
        {
            InitializeComponent();
            radioButtonDefault.Checked = true;
            comboBoxlevel.SelectedIndex = 0;
            groupBoxStep2.Enabled = groupBoxStep3.Enabled = false;
            buttonRandom.Enabled = false;
            SetDefaultValue();
        }

        private void SetDefaultValue()
        {
            _numBrick1 = _numBrick2 = _numBrick11 = _numBrick12 = 0;
            _numSteel3 = _numSteel4 = _numSteel13 = _numSteel14 = 0;
            _numWater5 = _numWater6 = _numWater15 = _numWater16 = 0;
            _numTrees7 = _numTrees8 = _numTrees17 = _numTrees18 = 0;
            _numIce9 = _numIce10 = _numIce19 = _numIce20 = 0;
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                labelFilename.Text = openFileDialog1.SafeFileName;
                groupBoxStep2.Enabled = groupBoxStep3.Enabled = true;
                _filePath = openFileDialog1.FileName;                
                _fileLines = File.ReadAllLines(_filePath);
                _numRow = _numCol = 0;
                GetInfoMapFromFile();
            }
        }
        //-------------------------------------------------------------
        // Đọc các thông tin về số dòng, số cột, kích thước ô tile.
        //-------------------------------------------------------------
        private void GetInfoMapFromFile()
        {
            int count = 0;
            foreach (string t in _fileLines)
            {
                if (count == 4)
                    break;
                //get numcol
                if (t.StartsWith("width="))
                {
                    _numCol = int.Parse(t.Substring(6));
                    count++;
                    continue;
                }
                //get num row
                if (t.StartsWith("height="))
                {
                    _numRow = int.Parse(t.Substring(7));
                    count++;
                    continue;
                }
                //get tile width
                if (t.StartsWith("tilewidth="))
                {
                    _tilewidth = int.Parse(t.Substring(10));
                    count++;
                    continue;
                }
                //get title height
                if (t.StartsWith("tileheight="))
                {
                    _tileheight = int.Parse(t.Substring(11));
                    count++;
                }
            }
        }


        private void buttonParse_Click(object sender, EventArgs e)
        {
            if (radioButtonCustom.Checked)
            {
                if (!ValidateTextbox())
                    return;
            }         
            if (_numCol == 0 || _numRow == 0)
            {
                MessageBox.Show("File not correct!","Error",MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            _mapMatrix = new string[_numRow][];
            for (int i = 0; i < _numRow; i++)
            {
                _mapMatrix[i] = new string[_numCol];
            }

            bool flag = false;
            _currentRow = 0;
            foreach (string line in _fileLines)
            {
                if (!flag)
                {
                    if (line.StartsWith("data="))
                    {
                        flag = true;
                    }               
                }
                else
                {
                    ReadLine(line);
                }
            }

            FixMap();
            ParseMap();
            WriteToFile();
        }

        //------------------------------
        // Đọc các giá trị trên dòng và đưa vào ma trận
        //------------------------------
        private void ReadLine(string line)
        {
            string[] itemInLine = line.Split(',');
            if (itemInLine[0] == "")
                return;
            for (int i = 0; i < _numCol; i++)
            {
                _mapMatrix[_currentRow][i] = itemInLine[i];
            }
            _currentRow++;
        }

        //------------------------------
        // Gán giá trị "0" cho vị trí đưa vào
        //------------------------------
        private void FixTile(ref string titlevalue )
        {
            List<string> list = new List<string>(new[] { "7", "8", "9", "10", "17", "18", "19", "20" });
            if (!list.Contains(titlevalue))
            {
                titlevalue = "0";
            }
        }

        //------------------------------
        // Fix Vị trí xuất hiện của player, tank địch, căn cứ không được có các đối tượng như gạch, thép, sông
        //------------------------------
        private void FixMap()
        {
            int row, col;
            //Goc trên bên trái
            for (row = 0; row < 4; row++)
            {
                for (col = 0; col < 4; col++)
                {
                    FixTile(ref _mapMatrix[row][col]);
                }
            }
            //Góc trên ở giữa
            for (row = 0; row < 4; row++)
            {
                for (col = 24; col < 28; col++)
                {
                    FixTile(ref _mapMatrix[row][col]);
                }
            }
            //Góc trên bên phải
            for (row = 0; row < 4; row++)
            {
                for (col = 48; col < 52; col++)
                {
                    FixTile(ref _mapMatrix[row][col]);
                }
            }
            //Vị trí căn cứ
            for (row = 48; row < 52; row++)
            {
                for (col = 24; col < 28; col++)
                {
                    FixTile(ref _mapMatrix[row][col]);
                }
            }
            //Vị trí player
            for (row = 48; row < 52; row++)
            {
                for (col = 18; col < 22; col++)
                {
                    FixTile(ref _mapMatrix[row][col]);
                }
            }
        }

        //------------------------------
        // Thay đổi giá trị mỗi phần tử trong ma trận
        // Giá trị mới = Số thứ tự xuất hiện*100 + (Giá trị cũ – 1)        
        // Ví dụ: Số 4 thứ 144 trên ma trận: 4 -> 14403     (144: số thứ tự, 3: ID - 1 ) 
        // Vị trí nào có giá trị = 0 sẽ được đưa về -1
        //------------------------------
        private void ParseMap()
        {
            int row, col, value;
            for (row = 0; row < _numRow; row++)
            {
                for (col = 0; col < _numCol; col++)
                {
                    value = int.Parse(_mapMatrix[row][col]);
                    switch (value)
                    {
                        case 1:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numBrick1 * 100).ToString();
                                _numBrick1++;
                                break;
                            }
                        case 2:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numBrick2 * 100).ToString();
                                _numBrick2++;
                                break;
                            }
                        case 3:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numSteel3 * 100).ToString();
                                _numSteel3++;
                                break;
                            }
                        case 4:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numSteel4 * 100).ToString();
                                _numSteel4++;
                                break;
                            }
                        case 5:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numWater5 * 100).ToString();
                                _numWater5++;
                                break;
                            }
                        case 6:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numWater6 * 100).ToString();
                                _numWater6++;
                                break;
                            }
                        case 7:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numTrees7 * 100).ToString();
                                _numTrees7++;
                                break;
                            }
                        case 8:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numTrees8 * 100).ToString();
                                _numTrees8++;
                                break;
                            }
                        case 9:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numIce9 * 100).ToString();
                                _numIce9++;
                                break;
                            }
                        case 10:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numIce10 * 100).ToString();
                                _numIce10++;
                                break;
                            }
                        case 11:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numBrick11 * 100).ToString();
                                _numBrick11++;
                                break;
                            }
                        case 12:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numBrick12 * 100).ToString();
                                _numBrick12++;
                                break;
                            }
                        case 13:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numSteel13 * 100).ToString();
                                _numSteel13++;
                                break;
                            }
                        case 14:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numSteel14 * 100).ToString();
                                _numSteel14++;
                                break;
                            }
                        case 15:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numWater15 * 100).ToString();
                                _numWater15++;
                                break;
                            }
                        case 16:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numWater16 * 100).ToString();
                                _numWater16++;
                                break;
                            }
                        case 17:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numTrees17 * 100).ToString();
                                _numTrees17++;
                                break;
                            }
                        case 18:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numTrees18 * 100).ToString();
                                _numTrees18++;
                                break;
                            }
                        case 19:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numIce19 * 100).ToString();
                                _numIce19++;
                                break;
                            }
                        case 20:
                            {
                                _mapMatrix[row][col] = (value - 1 + _numIce20 * 100).ToString();
                                _numIce20++;
                                break;
                            }
                        default:
                            {
                                _mapMatrix[row][col] = (value - 1).ToString();
                                break;
                            }

                    }
                }
            }
            SetDefaultValue();
        }

        //------------------------------
        // Ghi ma trận đã được chuyển đổi ra file txt
        // Chuẩn đầu ra: 
        //  Tổng số lượng tank địch
        //  Số lượng medium tank
        //  Số lượng light tank
        //  Số lượng heavy tank
        //  Số lượng super heavy tank
        //  Thứ tự xuất hiện từng loại
        //  Ma trận map đã chuyển đổi. 
        //------------------------------
        private void WriteToFile()
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (StreamWriter outputFile = new StreamWriter(saveFileDialog1.FileName, false)) //Thuộc tính false giúp replace, ko bị chèn thêm khi file đã có
                {
                    outputFile.WriteLine(textBoxTotal.Text);
                    outputFile.WriteLine(textBoxMedium.Text);
                    outputFile.WriteLine(textBoxLight.Text);
                    outputFile.WriteLine(textBoxHeavy.Text);
                    outputFile.WriteLine(textBoxSuper.Text);
                    outputFile.WriteLine(_order);
                    for (int i = 0; i < _numRow; i++)
                    {
                        outputFile.WriteLine(string.Join(",",_mapMatrix[i]));
                    }                
                }
                MessageBox.Show("Parse map completed!\n" + saveFileDialog1.FileName, "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void SetText(int[] num)
        {
            textBoxMedium.Text = num[0].ToString();
            textBoxLight.Text = num[1].ToString();
            textBoxHeavy.Text = num[2].ToString();
            textBoxSuper.Text = num[3].ToString();
            textBoxOrder.Text = _order;
        }

        //------------------------------
        // Phát sinh ngẫu nhiên thứ tự xuất hiện các loại tank địch
        //------------------------------
        private void RandomOrder()
        {
            _order = "";
            List<String> a = new List<string>(new[] {"0","1","2","3"});
            Random random = new Random();
            for (int i = 0; i < 4; i++)
            {        
                var temp = random.Next(0, a.Count-1);
                _order += a[temp];
                a.RemoveAt(temp);
            }
        }
        private void radioButtonRandom_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButtonRandom.Checked)
            {
                buttonRandom.Enabled = true;
                buttonRandom_Click(sender,e);
            }
            else
            {
                buttonRandom.Enabled = false;
            }       
        }

        private void buttonRandom_Click(object sender, EventArgs e)
        {
            textBoxTotal.Text = _maxEnemy.ToString();
            int max = _maxEnemy;
            Random random = new Random();
            for (int i = 0; i < 3; i++)
            {
                _numtank[i] = random.Next(0, max);
                max -= _numtank[i];
            }
            _numtank[3] = max;
            RandomOrder();
            SetText(_numtank);        
        }

        private void radioButtonCustom_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButtonCustom.Checked)
            {
                RandomOrder();
                textBoxMedium.ReadOnly = textBoxLight.ReadOnly = false;
                textBoxHeavy.ReadOnly = textBoxSuper.ReadOnly = false;
                textBoxTotal.ReadOnly = false;
                textBoxOrder.ReadOnly = false;               
            }
            else
            {
                textBoxMedium.ReadOnly = textBoxLight.ReadOnly = true;
                textBoxHeavy.ReadOnly = textBoxSuper.ReadOnly = true;
                textBoxTotal.ReadOnly = true;
                textBoxOrder.ReadOnly = true;
            }
        }

        private void radioButtonDefault_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButtonDefault.Checked)
            {
                textBoxTotal.Text = _maxEnemy.ToString();
                comboBoxlevel.Enabled = true;
                comboBoxlevel.SelectedIndex = -1;
            }
            else
            {
                comboBoxlevel.Enabled = false;
            }
        }

        private void comboBoxlevel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxlevel.SelectedIndex == 0)
            {
                _numtank = new[] {18, 2, 0, 0};
                _order = "0123";
            }
            if (comboBoxlevel.SelectedIndex == 1)
            {
                _numtank = new[] { 14, 4, 0, 2 };
                _order = "3102";
            }
            if (comboBoxlevel.SelectedIndex == 2)
            {
                _numtank = new[] { 14, 4, 0, 2 };
                _order = "0132";
            }
            if (comboBoxlevel.SelectedIndex == 3)
            {
                _numtank = new[] { 2, 5, 10, 3 };
                _order = "2103";
            }
            if (comboBoxlevel.SelectedIndex == 4)
            {
                _numtank = new[] { 8, 5, 5, 2 };
                _order = "2301";
            }
            /*
            See more level: http://strategywiki.org/wiki/Battle_City/Walkthrough
            */
            SetText(_numtank);
        }

        private void textBoxMedium_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = !char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar);
        }

        private bool ValidateTextbox()
        {
            if(textBoxMedium.Text == "" || textBoxLight.Text == "" ||
                textBoxHeavy.Text == "" || textBoxSuper.Text == "" || textBoxTotal.Text == "")
            {
                MessageBox.Show("Num tank textbox not be empty","Error",MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if((int.Parse(textBoxMedium.Text) + int.Parse(textBoxLight.Text) +
                int.Parse(textBoxHeavy.Text) + int.Parse(textBoxSuper.Text) != int.Parse(textBoxTotal.Text)))
            {
                MessageBox.Show("Number tank not correct", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if (int.Parse(textBoxTotal.Text) == 0)
            {
                MessageBox.Show("Total number tank must more than zero value ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            //Kiểm tra ô order
            List<char> list = new List<char>(new[] { '0', '1', '2', '3' });
            String orderText = textBoxOrder.Text;
            foreach (var item in orderText)
            {
                if (!list.Contains(item))
                {
                    MessageBox.Show("Only have '0', '1', '2', '3' in order string", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }
            for(int i=0;i<orderText.Length;i++)
            {
                if (orderText.LastIndexOf(orderText[i]) != i)
                {
                    MessageBox.Show("Duplicate order character", "Error", MessageBoxButtons.OK,MessageBoxIcon.Error);
                    return false;
                }
                    
            }
      
            return true;
        }
    }
}
