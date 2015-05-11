Imports System.IO
Imports VGMStreamCLR

Public Class Form1
    Private b As Boolean

    Private Property ExportCancelled As Boolean
        Get
            Return b
        End Get
        Set(value As Boolean)
            b = value
        End Set
    End Property

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

        ExportCancelled = False

        ProgressBar1.Value = 0
        ProgressBar1.Maximum = ListView1.Items.Count

        Label1.Visible = False
        txtOutputDir.Visible = False
        btnBrowse.Visible = False
        btnOpenFolder.Visible = False
        btnAbout.Visible = False
        btnStart.Visible = False
        lblCurrentFile.Visible = True
        ProgressBar1.Visible = True
        btnCancel.Visible = True

        Dim filenames As New List(Of String)
        For Each item As ListViewItem In ListView1.Items
            filenames.Add(item.Text)
        Next
        Task.Factory.StartNew(Sub()
                                  ExportSub(filenames)
                              End Sub)
    End Sub

    Private Sub ExportSub(filenames As IEnumerable(Of String))
        Try
            For Each infile As String In filenames
                If ExportCancelled Then
                    Exit For
                End If

                Dim name As String = Path.GetFileNameWithoutExtension(infile)
                Me.Invoke(New Action(Sub()
                                         lblCurrentFile.Text = Path.GetFileName(name)
                                     End Sub))

                Using audio As New VGMAudio(infile)
                    Dim rendered As New VGMRenderedAudio(audio)

                    Try
                        If chk0ToStart.Checked Then
                            Dim filename = txtOutputDir.Text & Path.DirectorySeparatorChar & name & " (beginning).wav"
                            File.WriteAllBytes(filename, rendered.ExportWav(0, audio.LoopStart))
                        End If
                        If chkStartToEnd.Checked Then
                            Dim filename = txtOutputDir.Text & Path.DirectorySeparatorChar & name & " (loop).wav"
                            File.WriteAllBytes(filename, rendered.ExportWav(audio.LoopStart, audio.LoopEnd - audio.LoopStart))
                        End If
                        If chk0ToEnd.Checked Then
                            Dim filename = txtOutputDir.Text & Path.DirectorySeparatorChar & name & ".wav"
                            File.WriteAllBytes(filename, rendered.ExportWav())
                        End If
                    Catch e As Exception
                        MessageBox.Show(e.Message, e.GetType().ToString(), MessageBoxButtons.OK, MessageBoxIcon.Error)
                    End Try
                End Using

                Me.BeginInvoke(New Action(Sub()
                                              ProgressBar1.Value += 1
                                          End Sub))
            Next
        Catch e As Exception
            MessageBox.Show(e.Message, e.GetType().ToString(), MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try

        Me.BeginInvoke(New Action(AddressOf FinishExportSub))
    End Sub

    Private Sub FinishExportSub()
        lblCurrentFile.Visible = False
        ProgressBar1.Visible = False
        btnCancel.Visible = False
        Label1.Visible = True
        txtOutputDir.Visible = True
        btnBrowse.Visible = True
        btnOpenFolder.Visible = True
        btnAbout.Visible = True
        btnStart.Visible = True
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
        MessageBox.Show("ExportLoop (GUI version)" & N & "© 2015 libertyernie, vgmstream contributors" & N & N & "https://github.com/libertyernie/vgmstream" & N & N &
                        "TODO: license here.")
    End Sub

    Private Sub btnCancel_Click(sender As Object, e As EventArgs) Handles btnCancel.Click
        ExportCancelled = True
    End Sub
End Class
