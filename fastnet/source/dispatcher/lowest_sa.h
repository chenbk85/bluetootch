#ifndef __NAMED_PIPE_LOWEST_SA_H__
#define __NAMED_PIPE_LOWEST_SA_H__
#include <Sddl.h>
#include <Windows.h>
 namespace named_pipe
 {
	class CLowSA
	{
	public:
		CLowSA():m_pTmpSD(NULL), m_bError(FALSE)
		{
			m_bError = CreateALowSA(&m_SA, &m_SD)?FALSE:TRUE;
		}

		~CLowSA()
		{
			if (m_pTmpSD != NULL)
			{
				::LocalFree(m_pTmpSD);
				m_pTmpSD = NULL;
			}
		}
		LPSECURITY_ATTRIBUTES GetSA()
		{
			if (m_bError) 
				return NULL;
			return &m_SA;
		}
		operator LPSECURITY_ATTRIBUTES ()
		{
			return GetSA();
		}

	protected:
		// ------------------------------------------------------------------------
		// ����		: CreateALowSA
		// ����		: ����һ����Ȩ�޵İ�ȫ������
		// ����ֵ	: BOOL 
		// ����		: SECURITY_ATTRIBUTES *pSA
		// ����		: SECURITY_DESCRIPTOR *pSecurityD
		// ��ע		: 
		// -------------------------------------------------------------------------
		BOOL CLowSA::CreateALowSA(SECURITY_ATTRIBUTES *pSA, SECURITY_DESCRIPTOR *pSecurityD)
		{
#define LOW_INTEGRITY_SDDL_SACL TEXT("S:(ML;;NW;;;LW)")

			if (m_pTmpSD != NULL)
			{
				::LocalFree(m_pTmpSD);
				m_pTmpSD = NULL;
			}

			// ��ʼ����ȫ����
			BOOL bFuncRet = FALSE;
			PACL pSacl = NULL;                  
			BOOL fSaclPresent = FALSE;
			BOOL fSaclDefaulted = FALSE;

			// �����vista�򴴽�һ����Ȩ�޵Ĺ����ڴ�
			pSA->nLength = sizeof(SECURITY_ATTRIBUTES);
			pSA->bInheritHandle = FALSE;
			pSA->lpSecurityDescriptor = pSecurityD;
			do 
			{
				// ��ʼ��һ����ȫ���������ڶ�����������ΪSECURITY_DESCRIPTOR_REVISION
				bFuncRet = ::InitializeSecurityDescriptor(pSA->lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
				if (!bFuncRet)
				{
					break;
				}

				// ����DACL�����ɷ��ʿ��Ʊ����˴�������һ���յ�dacl�����Ҳ�ʹ��Ĭ�ϵ�dacl
				bFuncRet = ::SetSecurityDescriptorDacl(pSA->lpSecurityDescriptor, TRUE, 0, FALSE);
				if (!bFuncRet)
				{
					break;
				}
				// ��һ����ȫ�������ַ���ת���ɰ�ȫ����������ȫ�������ַ����Ǹ���ʽ�����ַ���
				// �ڶ��������㶨ΪSDDL_REVISION_1
				// ���ĸ������Ƿ��ذ�ȫ�������ֽ���������Ϊ��
				// ���API�泤��
				bFuncRet = ::ConvertStringSecurityDescriptorToSecurityDescriptor(
					LOW_INTEGRITY_SDDL_SACL, 
					SDDL_REVISION_1, 
					&m_pTmpSD, NULL);	// xp�����api��ʧ�ܡ�
				if (!bFuncRet)
				{
					bFuncRet = TRUE;
					break;
				}

				// ����SACL��ϵͳ���ʿ����б�
				bFuncRet = ::GetSecurityDescriptorSacl(m_pTmpSD, &fSaclPresent, &pSacl, &fSaclDefaulted);
				if (!bFuncRet)
				{
					break;
				}
				bFuncRet = ::SetSecurityDescriptorSacl(pSA->lpSecurityDescriptor, TRUE, pSacl, FALSE);
				if (!bFuncRet)
				{
					break;
				}

				bFuncRet = TRUE;

			} while(0);

			return bFuncRet;
		}
	private:
		BOOL m_bError;
		SECURITY_ATTRIBUTES m_SA;
		SECURITY_DESCRIPTOR m_SD;
		PSECURITY_DESCRIPTOR m_pTmpSD;
	};
}

#endif//BD_IPC_H__
