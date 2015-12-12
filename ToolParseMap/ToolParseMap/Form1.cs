using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace ToolParseMap
{
    public partial class Form1 : Form
    {
        private string[] _fileLines;
        private string _filePath;
        private bool _flag;
        private int _numCol;
        private int _numRow;
        private int _tilewidth;
        private int _tileheight;
        private string[][] _mapMatrix;
        private int _currentRow ;
        private int _maxEnemy = 20;
        private int[] _numtank = new int[4];
        private string order = "";
        //type Brick
        private int _numBrick1;
        private int _numBrick2;
        private int _numBrick11;
        private int _numBrick12;
        //type Steel
        private int _numSteel3;
        private int _numSteel4;
        private int _numSteel13;
        private int _numSteel14;
        //type water
        private int _numWater5;
        private int _numWater6;
        private int _numWater15;
        private int _numWater16;
        //type trees
        private int _numTrees7;
        private int _numTrees8;
        private int _numTrees17;
        private int _numTrees18;
        //type ice
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
            _flag = false;
            _currentRow = 0;
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
                _filePath = openFileDialog1.FileName;
                groupBoxStep2.Enabled = groupBoxStep3.Enabled = true;
            }
        }

        private void getInfoMapFromFile()
        {
            int count = 0;
            foreach (string t in _fileLines)
            {
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
                if (t.StartsWith("_tilewidth="))
                {
                    _tilewidth = int.Parse(t.Substring(10));
                    count++;
                    continue;
                }
                //get title height
                if (t.StartsWith("_tileheight="))
                {
                    _tileheight = int.Parse(t.Substring(11));
                    count++;
                    continue;
                }
                if(count==4)
                    break;
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            if (radioButtonCustom.Checked == true)
            {
                if (!validateTextbox())
                    return;
            }         
            _fileLines = File.ReadAllLines(_filePath);
            getInfoMapFromFile();

            if (_numCol == 0 || _numRow == 0)
            {
                MessageBox.Show("File not correct!","Warning",MessageBoxButtons.OK);
                return;
            }
            _mapMatrix = new string[_numRow][];
            for (int i = 0; i < _numRow; i++)
            {
                _mapMatrix[i] = new string[_numCol];
            }

            foreach (string t in _fileLines)
            {
                if (!_flag)
                {
                    if (t.StartsWith("data="))
                    {
                        _flag = true;
                        continue;
                    }               
                }
                else
                {
                    readMap(t);
                }
            }

            fixMap();
            parseMap();
            WriteToFile();
            _flag = false;
            _currentRow = 0;
        }

        private void readMap(string line)
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

        private void fixTile(ref string titlevalue )
        {
            List<string> list = new List<string>(new string[] { "7", "8", "9", "10", "17", "18", "19", "20" });
            if (!list.Contains(titlevalue))
            {
                titlevalue = "0";
            }
        }
        private void fixMap()
        {
            int i, j;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    fixTile(ref _mapMatrix[i][j]);
                }
            }
            for (i = 0; i < 4; i++)
            {
                for (j = 24; j < 28; j++)
                {
                    fixTile(ref _mapMatrix[i][j]);
                }
            }
            for (i = 0; i < 4; i++)
            {
                for (j = 48; j < 52; j++)
                {
                    fixTile(ref _mapMatrix[i][j]);
                }
            }
            for (i = 48; i < 52; i++)
            {
                for (j = 24; j < 28; j++)
                {
                    fixTile(ref _mapMatrix[i][j]);
                }
            }
            for (i = 48; i < 52; i++)
            {
                for (j = 18; j < 22; j++)
                {
                    fixTile(ref _mapMatrix[i][j]);
                }
            }
        }
        private void parseMap()
        {
            int i, j, temp;
            for (i = 0; i < _numRow; i++)
            {
                for (j = 0; j < _numCol; j++)
                {
                    temp = int.Parse(_mapMatrix[i][j]);
                    switch (temp)
                    {
                        case 1:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numBrick1 * 100).ToString();
                                _numBrick1++;
                                break;
                            }
                        case 2:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numBrick2 * 100).ToString();
                                _numBrick2++;
                                break;
                            }
                        case 3:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numSteel3 * 100).ToString();
                                _numSteel3++;
                                break;
                            }
                        case 4:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numSteel4 * 100).ToString();
                                _numSteel4++;
                                break;
                            }
                        case 5:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numWater5 * 100).ToString();
                                _numWater5++;
                                break;
                            }
                        case 6:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numWater6 * 100).ToString();
                                _numWater6++;
                                break;
                            }
                        case 7:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numTrees7 * 100).ToString();
                                _numTrees7++;
                                break;
                            }
                        case 8:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numTrees8 * 100).ToString();
                                _numTrees8++;
                                break;
                            }
                        case 9:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numIce9 * 100).ToString();
                                _numIce9++;
                                break;
                            }
                        case 10:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numIce10 * 100).ToString();
                                _numIce10++;
                                break;
                            }
                        case 11:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numBrick11 * 100).ToString();
                                _numBrick11++;
                                break;
                            }
                        case 12:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numBrick12 * 100).ToString();
                                _numBrick12++;
                                break;
                            }
                        case 13:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numSteel13 * 100).ToString();
                                _numSteel13++;
                                break;
                            }
                        case 14:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numSteel14 * 100).ToString();
                                _numSteel14++;
                                break;
                            }
                        case 15:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numWater15 * 100).ToString();
                                _numWater15++;
                                break;
                            }
                        case 16:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numWater16 * 100).ToString();
                                _numWater16++;
                                break;
                            }
                        case 17:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numTrees17 * 100).ToString();
                                _numTrees17++;
                                break;
                            }
                        case 18:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numTrees18 * 100).ToString();
                                _numTrees18++;
                                break;
                            }
                        case 19:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numIce19 * 100).ToString();
                                _numIce19++;
                                break;
                            }
                        case 20:
                            {
                                _mapMatrix[i][j] = (temp - 1 + _numIce20 * 100).ToString();
                                _numIce20++;
                                break;
                            }
                        default:
                            {
                                _mapMatrix[i][j] = (temp - 1).ToString();
                                break;
                            }

                    }
                }
            }
        }
        
        private void WriteToFile()
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (StreamWriter outputFile = new StreamWriter(saveFileDialog1.FileName, false))
                {
                    outputFile.WriteLine(textBoxTotal.Text);
                    outputFile.WriteLine(textBoxMedium.Text);
                    outputFile.WriteLine(textBoxLight.Text);
                    outputFile.WriteLine(textBoxHeavy.Text);
                    outputFile.WriteLine(textBoxSuper.Text);
                    outputFile.WriteLine(order);
                    for (int i = 0; i < _numRow; i++)
                    {
                        outputFile.WriteLine(string.Join(",",_mapMatrix[i]));
                    }                
                }
                MessageBox.Show("Parse map completed!\n" + saveFileDialog1.FileName, "Success", MessageBoxButtons.OK);
            }
        }

        private void setText(int[] num)
        {
            textBoxMedium.Text = num[0].ToString();
            textBoxLight.Text = num[1].ToString();
            textBoxHeavy.Text = num[2].ToString();
            textBoxSuper.Text = num[3].ToString();
        }
            
        private void randomOrder()
        {
            order = "";
            List<String> a = new List<string>(new string[] {"0","1","2","3"});            
            int temp;
            Random random = new Random();
            for (int i = 0; i < 4; i++)
            {        
                temp = random.Next(0, a.Count-1);
                order += a[temp];
                a.RemoveAt(temp);
            }
        }
        private void radioButtonRandom_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButtonRandom.Checked)
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
                setText(_numtank);
            }
            randomOrder();
        }

        private void radioButtonCustom_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButtonCustom.Checked)
            {
                textBoxMedium.ReadOnly = textBoxLight.ReadOnly = false;
                textBoxHeavy.ReadOnly = textBoxSuper.ReadOnly = false;
                textBoxTotal.ReadOnly = false;
                randomOrder();
            }
            else
            {
                textBoxMedium.ReadOnly = textBoxLight.ReadOnly = true;
                textBoxHeavy.ReadOnly = textBoxSuper.ReadOnly = true;
                textBoxTotal.ReadOnly = true;
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
                order = "0123";
            }
            if (comboBoxlevel.SelectedIndex == 1)
            {
                _numtank = new[] { 14, 4, 0, 2 };
                order = "3102";
            }
            if (comboBoxlevel.SelectedIndex == 2)
            {
                _numtank = new[] { 14, 4, 0, 2 };
                order = "0132";
            }
            if (comboBoxlevel.SelectedIndex == 3)
            {
                _numtank = new[] { 2, 5, 10, 3 };
                order = "2103";
            }
            if (comboBoxlevel.SelectedIndex == 4)
            {
                _numtank = new[] { 8, 5, 5, 2 };
                order = "2301";
            }
            /*
            See more level: http://strategywiki.org/wiki/Battle_City/Walkthrough
            */
            setText(_numtank);
        }

        private void textBoxMedium_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = !char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar);
        }

        private bool validateTextbox()
        {
            if(textBoxMedium.Text == "" || textBoxLight.Text == "" ||
                textBoxHeavy.Text == "" || textBoxSuper.Text == "" || textBoxTotal.Text == "")
            {
                MessageBox.Show("Num tank text box not be empty","Error",MessageBoxButtons.OK);
                return false;
            }
            if((int.Parse(textBoxMedium.Text) + int.Parse(textBoxLight.Text) +
                int.Parse(textBoxHeavy.Text) + int.Parse(textBoxSuper.Text) != int.Parse(textBoxTotal.Text)))
            {
                MessageBox.Show("Number tank not correct ", "Error", MessageBoxButtons.OK);
                return false;
            }
            return true;
        }
    }
}
