object Main: TMain
  Left = 237
  Top = 114
  Width = 719
  Height = 477
  Caption = 
    #1059#1090#1080#1083#1080#1090#1072' '#1076#1083#1103' '#1089#1086#1079#1076#1072#1085#1080#1103' '#1073#1080#1073#1083#1080#1086#1090#1077#1082' '#1089#1080#1075#1085#1072#1090#1091#1088'. '#1047#1072#1081#1094#1077#1074' '#1054'.'#1042'., 2003-2006 ' +
    '(Oracle)'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object StatusBar: TStatusBar
    Left = 0
    Top = 424
    Width = 711
    Height = 19
    Panels = <
      item
        Width = 400
      end
      item
        Width = 120
      end
      item
        Width = 50
      end>
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 711
    Height = 424
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1086#1077' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1077
      DesignSize = (
        703
        393)
      object Label1: TLabel
        Left = 3
        Top = 10
        Width = 108
        Height = 16
        Caption = #1057#1090#1072#1088#1090#1086#1074#1099#1081' '#1087#1091#1090#1100':'
      end
      object deStartDir: TDirectoryEdit
        Left = 114
        Top = 4
        Width = 589
        Height = 21
        NumGlyphs = 1
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
        Text = 'c:\'
      end
      object GroupBox1: TGroupBox
        Left = -7
        Top = 64
        Width = 710
        Height = 317
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = ' '#1055#1088#1086#1090#1086#1082#1086#1083' '
        TabOrder = 1
        object LogMemo: TMemo
          Left = 2
          Top = 18
          Width = 706
          Height = 297
          Align = alClient
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
        end
      end
      object mbStart: TBitBtn
        Left = 8
        Top = 35
        Width = 75
        Height = 25
        Caption = #1055#1091#1089#1082
        TabOrder = 2
        OnClick = mbStartClick
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
          FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD020202
          020202FDFDFDFDFDFDFDFDFDFDFDFDFDFDA4A4A4A4A4A4FDFDFDFDFDFDFDFDFD
          FDFDFDFDFD020202020202FDFDFDFDFDFDFDFDFDFDFDFD020202020202020202
          02FDFDFDFDFDFDFDFDFDFDA4A4A4A4A4A4A4A4A4A4FDFDFDFDFDFDFDFDFDFD02
          020202020202020202FDFDFDFDFDFDFDFDFD020228282828282828020202FDFD
          FDFDFDFDFDFDA4A4F7F7F7F7F7F7F7F7A4A4FDFDFDFDFDFDFDFD020228282828
          282828020202FDFDFDFDFDFDFD0228282810102828282828280202FDFDFDFDFD
          FDA4F7F7F7A4A4F7F7F7F7F7F7A4A4FDFDFDFDFDFD0228282810102828282828
          280202FDFDFDFDFD022828282818FF182828282828280202FDFDFDFDA4F7F7F7
          F7A4FFA4F7F7F7F7F7F7A4A4FDFDFDFD022828282818FB182828282828280202
          FDFDFDFD022828282818FFFF1828282828280202FDFDFDFDA4F7F7F7F7A4FFFF
          A4F7F7F7F7F7A4A4FDFDFDFD022828282818FBFB1828282828280202FDFDFD02
          282828282818FFFFFF1828282828280202FDFD07F7F7F7F7F7A4FFFFFFA4F7F7
          F7F7F7A4A4FDFD02282828282818FBFBFB1828282828280202FDFD2828282828
          2818FFFFFFFF18282828280202FDFDF7F7F7F7F7F7A4FFFFFFFFA4F7F7F7F7A4
          A4FDFD28282828282818FBFBFBFB18282828280202FDFD28282828282818FFFF
          FFFFFF182828280202FDFD07F7F7F7F7F7A4FFFFFFFFFFA4F7F7F7A4A4FDFD28
          282828282818FBFBFBFBFB182828280202FDFD28282828282818FFFFFFFFFFFF
          1828280202FDFD07F7F7F7F7F7A4FFFFFFFFFFFFA4F7F7A4A4FDFD2828282828
          2818FBFBFBFBFBFB1828280202FDFD28282828282818FFFFFFFFFF1828282802
          02FDFD07F7F7F7F7F7A4FFFFFFFFFFA4F7F7F7A4A4FDFD28282828282818FBFB
          FBFBFB182828280202FDFD28282828282818FFFFFFFF18282828280202FDFD07
          F7F7F7F7F7A4FFFFFFFFA4F7F7F7F7A4A4FDFD28282828282818FBFBFBFB1828
          2828280202FDFDFD282828282818FFFFFF18282828282802FDFDFDFD07F7F7F7
          F7A4FFFFFFA4F7F7F7F7F7A4FDFDFDFD282828282818FBFBFB18282828282802
          FDFDFDFD283028282818FFFF1828282828280202FDFDFDFDF7F7F7F7F7A4FFFF
          A4F7F7F7F7F7A4A4FDFDFDFD283028282818FBFB1828282828280202FDFDFDFD
          FD2830282818FF1828282828280202FDFDFDFDFDFD07F7F7F7A4FFA4F7F7F7F7
          F7A4A4FDFDFDFDFDFD2830282818FB1828282828280202FDFDFDFDFDFDFD2830
          28181828282828280202FDFDFDFDFDFDFDFD07F7F7A4A4F7F7F7F7F7A4A4FDFD
          FDFDFDFDFDFD283028181828282828280202FDFDFDFDFDFDFDFDFD2830282828
          2828282828FDFDFDFDFDFDFDFDFDFD07F7F7F7F7F7F7F7F7A4FDFDFDFDFDFDFD
          FDFDFD28302828282828282828FDFDFDFDFDFDFDFDFDFDFDFD282828282828FD
          FDFDFDFDFDFDFDFDFDFDFDFDFDF707070707F7FDFDFDFDFDFDFDFDFDFDFDFDFD
          FD282828282828FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD
          FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD
          FDFDFDFDFDFDFDFDFDFD}
        NumGlyphs = 3
      end
      object mbStop: TBitBtn
        Left = 88
        Top = 35
        Width = 75
        Height = 25
        Caption = #1057#1090#1086#1087
        TabOrder = 3
        OnClick = mbStopClick
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
      object mbSaveLog: TBitBtn
        Left = 521
        Top = 31
        Width = 179
        Height = 25
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1088#1086#1090#1086#1082#1086#1083
        TabOrder = 4
        OnClick = mbSaveLogClick
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000010000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFF0000000000000FF03300000088030FF03300000088030FF03300000088
          030FF03300000000030FF03333333333330FF03300000000330FF03088888888
          030FF03088888888030FF03088888888030FF03088888888030FF03088888888
          000FF03088888888080FF00000000000000FFFFFFFFFFFFFFFFF}
      end
      object CheckBox1: TCheckBox
        Left = 168
        Top = 27
        Width = 137
        Height = 17
        Caption = #1057#1088#1072#1074#1085#1077#1085#1080#1077
        Checked = True
        State = cbChecked
        TabOrder = 5
      end
      object cbAllPE: TCheckBox
        Left = 168
        Top = 43
        Width = 145
        Height = 17
        Caption = #1042#1089#1077' PE '#1092#1072#1081#1083#1099
        TabOrder = 6
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1056#1091#1095#1085#1086#1077' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1077
      ImageIndex = 1
      DesignSize = (
        703
        393)
      object feGoodFile: TFilenameEdit
        Left = 0
        Top = 8
        Width = 697
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        NumGlyphs = 1
        TabOrder = 0
      end
      object Button1: TButton
        Left = 1
        Top = 33
        Width = 120
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 1
        OnClick = Button1Click
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 112
    Top = 144
  end
  object SaveDialog: TSaveDialog
    Left = 80
    Top = 143
  end
  object OracleSession1: TOracleSession
    LogonUsername = 'avz'
    LogonPassword = 'aes254'
    LogonDatabase = 'VIRLAB'
    Connected = True
    Left = 168
    Top = 119
  end
  object GoodFilesDataSet: TOracleDataSet
    SQL.Strings = (
      'select g.*, g.rowid from AVZT_GOOD_FILES g')
    QBEDefinition.QBEFieldDefs = {
      04000000100000000A00000047524F55505F434F444501000000000008000000
      46494C454E414D450100000000000800000046494C4553495A45010000000000
      0500000049534558450100000000000400000049535045010000000000020000
      0053310100000000000200000053320100000000000200000053330100000000
      000200000053340100000000000700000053554D4D4352430100000000000300
      00004D44350100000000000800000046494C45444154450100000000000F0000
      0046494C454445534352495054494F4E0100000000000B00000046494C455645
      5253494F4E01000000000008000000444154455F414444010000000000080000
      0041565A5F46494C45010000000000}
    QueryAllRecords = False
    Session = OracleSession1
    Active = True
    Left = 200
    Top = 119
  end
  object CheckFileOracleQuery: TOracleQuery
    SQL.Strings = (
      'SELECT MD5'
      'FROM AVZ.AVZT_GOOD_FILES'
      'WHERE MD5 = :MD5'
      '')
    Session = OracleSession1
    Variables.Data = {0300000001000000040000003A4D4435050000000000000000000000}
    Left = 240
    Top = 119
  end
end
