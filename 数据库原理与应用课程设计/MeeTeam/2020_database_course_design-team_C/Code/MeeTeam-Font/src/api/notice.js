import request from '@/utils/request'

export function get_notice(params) {
    /*根据id获取单条公告内容*/
    return request({
        url: '/notice/get_by_id',
        method: 'get',
        params: {
            id: params.id
        }
    })
}

export function get_all() {
    /*根据id获取单条公告内容*/
    return request({
        url: '/notice/get_all',
        method: 'get',
    })
}

export function create_notice(params) {
    /*创建新公告*/
    return request({
        url: '/notice/post',
        method: 'post',
        params: { not: params }
    })
}