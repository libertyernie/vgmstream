Imports System.IO
Imports System.Text

Public Class Form1
    ''' <summary>
    ''' Quote pathnames in arguments so other Windows applications will understand them.
    ''' Converted from https://github.com/gfxmonk/csharp-quote-argv/blob/master/QuoteArguments.cs
    ''' </summary>
    ''' <param name="arg">An argument to escape</param>
    ''' <returns>The escaped argument</returns>
    Private Shared Function QuoteArgument(arg As String) As String
        Dim backslashes As Integer = 0

        Dim sb As New StringBuilder

        Dim needquote As Boolean = arg.Length = 0 Or arg.Contains(" ") Or arg.Contains(vbTab)
        If needquote Then
            sb.Append(""""c)
        End If

        For Each c As Char In arg
            If c = "\"c Then
                backslashes += 1
            ElseIf c = """"c Then
                ' Make sure pending backslashes are doubled
                sb.Append(New String("\"c, backslashes * 2))
                backslashes = 0

                ' Append a backslash-escaped double quote
                sb.Append("\""")
            Else
                If backslashes > 0 Then
                    sb.Append(New String("\"c, backslashes))
                    backslashes = 0
                End If

                sb.Append(c)
            End If
        Next

        If backslashes > 0 Then
            sb.Append(New String("\"c, backslashes))
        End If

        If needquote Then
            sb.Append(New String("\"c, backslashes))
            sb.Append(""""c)
        End If

        Return sb.ToString()
    End Function

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        txtOutputDir.Text = Environment.CurrentDirectory
    End Sub

    Private Sub btnAdd_Click(sender As Object, e As EventArgs) Handles btnAdd.Click
        If OpenFileDialog1.ShowDialog = DialogResult.OK Then
            For Each f In OpenFileDialog1.FileNames
                ListView1.Items.Add(f)
            Next
        End If
    End Sub

    Private Sub btnRemove_Click(sender As Object, e As EventArgs) Handles btnRemove.Click
        For Each item As ListViewItem In ListView1.SelectedItems
            ListView1.Items.Remove(item)
        Next
    End Sub

    Private Sub ListView1_DragEnter(sender As Object, e As DragEventArgs) Handles ListView1.DragEnter
        If e.Data.GetDataPresent(DataFormats.FileDrop) Then
            e.Effect = DragDropEffects.Link
        End If
    End Sub

    Private Sub ListView1_DragDrop(sender As Object, e As DragEventArgs) Handles ListView1.DragDrop
        If e.Data.GetDataPresent(DataFormats.FileDrop) Then
            Dim filenames As String() = e.Data.GetData(DataFormats.FileDrop)
            For Each filename As String In filenames
                ListView1.Items.Add(filename)
            Next
        End If
    End Sub

    Private Sub btnBrowse_Click(sender As Object, e As EventArgs) Handles btnBrowse.Click
        If Not String.IsNullOrEmpty(txtOutputDir.Text) Then
            FolderBrowserDialog1.SelectedPath = txtOutputDir.Text
            If FolderBrowserDialog1.ShowDialog = DialogResult.OK Then
                txtOutputDir.Text = FolderBrowserDialog1.SelectedPath
            End If
        End If
    End Sub

    Private Sub btnStart_Click(sender As Object, e As EventArgs) Handles btnStart.Click
        If Not Directory.Exists(txtOutputDir.Text) Then
            MessageBox.Show("The specified output directory does not exist.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Exit Sub
        End If

        Dim args As String = ""

        Dim wavsPerBrstm As Integer
        If chk0ToStart.Checked Then
            wavsPerBrstm += 1
            args += "-0L "
        End If
        If chkStartToEnd.Checked Then
            wavsPerBrstm += 1
            args += "-LE "
        End If
        If chk0ToEnd.Checked Then
            wavsPerBrstm += 1
            args += "-0E "
        End If

        For Each item As ListViewItem In ListView1.Items
            If item.Text.Contains("""") Then
                Throw New Exception("Double quotes are not allowed in pathnames.")
            End If
            If item.Text.Contains("\\") Then
                Throw New Exception("Consecutive backslashes are not allowed in pathnames.")
            End If
            args += """" + item.Text + """ "
        Next

        Dim startInfo As New ProcessStartInfo("exportloop.exe", args)
        startInfo.RedirectStandardOutput = True
        startInfo.RedirectStandardError = True
        startInfo.ErrorDialog = True
        startInfo.UseShellExecute = False
        startInfo.CreateNoWindow = True

        Dim p As Process = Process.Start(startInfo)
        Dim out As StreamReader = p.StandardOutput

        Dim s As New Stopwatch
        s.Start()

        While Not out.EndOfStream
            Console.WriteLine(s.Elapsed.ToString & Me.Text)
            s.Restart()
            Me.Text = out.ReadLine()
        End While
        p.WaitForExit()
        MessageBox.Show(p.ExitCode)
    End Sub

    Private Sub btnOpenFolder_Click(sender As Object, e As EventArgs) Handles btnOpenFolder.Click
        If Not Directory.Exists(txtOutputDir.Text) Then
            MessageBox.Show("The specified output directory does not exist.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Exit Sub
        End If

        Process.Start(txtOutputDir.Text)
    End Sub

    Private Sub btnAbout_Click(sender As Object, e As EventArgs) Handles btnAbout.Click
        Dim N = Environment.NewLine
        MessageBox.Show("BRSTM to WAV Converter" & N & "© 2015 libertyernie" & N & N & "https://github.com/libertyernie/BrstmToWav" & N & N &
                        "This program is provided as-is without any warranty, implied or otherwise. By using this program, the end user agrees to take full responsibility regarding its proper and lawful use. The authors/hosts/distributors cannot be held responsible for any damage resulting in the use of this program, nor can they be held accountable for the manner in which it is used.")
    End Sub
End Class
