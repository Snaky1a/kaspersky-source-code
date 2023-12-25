object BackupScriptsDLG: TBackupScriptsDLG
  Left = 192
  Top = 114
  Width = 607
  Height = 434
  Caption = '$AVZ1186'
  Color = clBtnFace
  Constraints.MinHeight = 200
  Constraints.MinWidth = 400
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object cbRepairScriptList: TCheckListBox
    Left = 0
    Top = 0
    Width = 599
    Height = 369
    Align = alClient
    ItemHeight = 16
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 369
    Width = 599
    Height = 31
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      599
      31)
    object BitBtn1: TBitBtn
      Left = 505
      Top = 3
      Width = 89
      Height = 24
      Anchors = [akTop, akRight]
      Caption = '$AVZ0266'
      TabOrder = 0
      Kind = bkCancel
    end
    object mbRunScripts: TBitBtn
      Left = 4
      Top = 3
      Width = 269
      Height = 25
      Caption = '$AVZ1187'
      TabOrder = 1
      OnClick = mbRunScriptsClick
      Glyph.Data = {
        F6000000424DF600000000000000760000002800000010000000100000000100
        0400000000008000000000000000000000001000000010000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFF717FFFFFFFFFFFFF111FFFFFFFFFFFFF717FFFFFFFFFFFF
        FFFF00000000007FFF1F08BFBFB8070FF7177000000000FFF111F08888880FFF
        F111F0FBFBFB07FFF111F70F8888F07FF111FF70BFBFBF0FF111FFF088888807
        FF1FFF00000000007FFFFF08BFBFB8070FFFFFF000000000FFFF}
    end
    object mbStopScript: TBitBtn
      Left = 277
      Top = 3
      Width = 203
      Height = 25
      Hint = '$AVZ0600'
      Caption = '$AVZ0597'
      TabOrder = 2
      OnClick = mbStopScriptClick
      Glyph.Data = {
        E6080000424DE60800000000000036040000280000003C000000140000000100
        080000000000B004000000000000000000000001000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
        A6000020400000206000002080000020A0000020C0000020E000004000000040
        20000040400000406000004080000040A0000040C0000040E000006000000060
        20000060400000606000006080000060A0000060C0000060E000008000000080
        20000080400000806000008080000080A0000080C0000080E00000A0000000A0
        200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
        200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
        200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
        20004000400040006000400080004000A0004000C0004000E000402000004020
        20004020400040206000402080004020A0004020C0004020E000404000004040
        20004040400040406000404080004040A0004040C0004040E000406000004060
        20004060400040606000406080004060A0004060C0004060E000408000004080
        20004080400040806000408080004080A0004080C0004080E00040A0000040A0
        200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
        200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
        200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
        20008000400080006000800080008000A0008000C0008000E000802000008020
        20008020400080206000802080008020A0008020C0008020E000804000008040
        20008040400080406000804080008040A0008040C0008040E000806000008060
        20008060400080606000806080008060A0008060C0008060E000808000008080
        20008080400080806000808080008080A0008080C0008080E00080A0000080A0
        200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
        200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
        200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
        2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
        2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
        2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
        2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
        2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
        2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
        2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FDFDFDFDFDFD
        FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD
        FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD040404
        040404FDFDFDFDFDFDFDFDFDFDFDFDFDFDA4A4A4A4A4A4FDFDFDFDFDFDFDFDFD
        FDFDFDFDFD040404040404FDFDFDFDFDFDFDFDFDFDFDFD040404040404040404
        04FDFDFDFDFDFDFDFDFDFDA4A4A4A4A4A4A4A4A4A4FDFDFDFDFDFDFDFDFDFD04
        040404040404040404FDFDFDFDFDFDFDFDFD0404C0C0C0C0C0C0C0040404FDFD
        FDFDFDFDFDFDA4A4A4A4A4A4A4A4A4A4A4A4FDFDFDFDFDFDFDFD0404C0C0C0C0
        C0C0C0040404FDFDFDFDFDFDFDFCC0C0C0C0C0C0C0C0C0C0C00404FDFDFDFDFD
        FDA4A4A4A4A4A4A4A4A4A4A4A4A4A4FDFDFDFDFDFDFCC0C0C0C0C0C0C0C0C0C0
        C00404FDFDFDFDFD04C0C0C0C0C0C0C0C0C0C0C0C0C00404FDFDFDFDA4A4A4A4
        A4A4A4A4A4A4A4A4A4A4A4A4FDFDFDFD04C0C0C0C0C0C0C0C0C0C0C0C0C00404
        FDFDFDFD04C0C0040404040404040404C0C00404FDFDFDFDA4A4A4A4A4A4A4A4
        A4A4A4A4A4A4A4A4FDFDFDFD04C0C0040404040404040404C0C00404FDFDFDFC
        C0C0C004FFFFFF04FFFFFF04C0C0C00404FDFDF7A4A4A4A4FFFFFFA4FFFFFFA4
        A4A4A4A4A4FDFDFCC0C0C004FBFBFB04FBFBFB04C0C0C00404FDFDFCC0C0C004
        FFFFFF04FFFFFF04C0C0C00404FDFDF7A4A4A4A4FFFFFFA4FFFFFFA4A4A4A4A4
        A4FDFDFCC0C0C004FBFBFB04FBFBFB04C0C0C00404FDFDFCC0C0C004FFFFFF04
        FFFFFF04C0C0C00404FDFDF7A4A4A4A4FFFFFFA4FFFFFFA4A4A4A4A4A4FDFDFC
        C0C0C004FBFBFB04FBFBFB04C0C0C00404FDFDFCC0C0C004FFFFFF04FFFFFF04
        C0C0C00404FDFDF7A4A4A4A4FFFFFFA4FFFFFFA4A4A4A4A4A4FDFDFCC0C0C004
        FBFBFB04FBFBFB04C0C0C00404FDFDFCC0C0C004FFFFFF04FFFFFF04C0C0C004
        04FDFDF7A4A4A4A4FFFFFFA4FFFFFFA4A4A4A4A4A4FDFDFCC0C0C004FBFBFB04
        FBFBFB04C0C0C00404FDFDFCFCC0C004FFFFFF04FFFFFF04C0C0C00404FDFDF7
        A4A4A4A4FFFFFFA4FFFFFFA4A4A4A4A4A4FDFDFCFCC0C004FBFBFB04FBFBFB04
        C0C0C00404FDFDFDFCC0C004FFFFFF04FFFFFF04C0C0C004FDFDFDFDF7A4A4A4
        FFFFFFA4FFFFFFA4A4A4A4A4FDFDFDFDFCC0C004FBFBFB04FBFBFB04C0C0C004
        FDFDFDFDFCFCC0040404040404040404C0C00404FDFDFDFDF7A4A4A4A4A4A4A4
        A4A4A4A4A4A4A4A4FDFDFDFDFCFCC0040404040404040404C0C00404FDFDFDFD
        FDFCFCC0C0C0C0C0C0C0C0C0C00404FDFDFDFDFDFDF7F7A4A4A4A4A4A4A4A4A4
        A4A4A4FDFDFDFDFDFDFCFCC0C0C0C0C0C0C0C0C0C00404FDFDFDFDFDFDFDFCFC
        C0FCFCC0C0C0C0C00404FDFDFDFDFDFDFDFDF7F7A4A4A4A4A4A4A4A4A4A4FDFD
        FDFDFDFDFDFDFCFCC0FCFCC0C0C0C0C00404FDFDFDFDFDFDFDFDFDFCFCC0C0C0
        C0C0C0FCFCFDFDFDFDFDFDFDFDFDFDF7A4A4A4A4A4A4A4A4A4FDFDFDFDFDFDFD
        FDFDFDFCFCC0C0C0C0C0C0FCFCFDFDFDFDFDFDFDFDFDFDFDFDFCFCFCFCFCFCFD
        FDFDFDFDFDFDFDFDFDFDFDFDFDF7F7F7F7F7F7FDFDFDFDFDFDFDFDFDFDFDFDFD
        FDFCFCFCFCFCFCFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD
        FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD
        FDFDFDFDFDFDFDFDFDFD}
      NumGlyphs = 3
    end
  end
end
