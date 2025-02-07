import request from '@/utils/request'

export function deleteproject(params) {
  /*删除组队需求 */
    return request({
      url: '/Project/deleteProject',
      method: 'delete',
      params:{
        project_id:params.project_id
      }
    })
  }
  export function changelist(params) {
    /*创建组队需求 */
    return request({
      url: '/GroupRequirement/ChangeGroupRequirement',
      method: 'post',
      params:{
        require_id:params.require_id,
        purpose:params.purpose,
        team_type:params.team_type,
        team_limit:params.team_limit,
        details:params.details,       
        require_status:params.require_status,
        originator_id:params.originator_id,
        project_id:params.project_id,
        region:params.region,
        team_type_details:params.team_type_detail,
        requirement_name:params.requirement_name,
      }
    })
  }
